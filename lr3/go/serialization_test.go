package main

import (
	"os"
	"path/filepath"
	"reflect"
	"testing"
)

func fixtures() []struct {
	name   string
	create func() any
	empty  func() any
} {
	return []struct {
		name   string
		create func() any
		empty  func() any
	}{
		{"array", func() any {
			a := NewArray()
			for _, s := range []string{"one", "two words", "", `"quote"`, "a:b", "line\nbreak", "Привет"} {
				a.PushBack(s)
			}
			return a
		}, func() any { return NewArray() }},
		{"slist", func() any { a := NewSList(); a.PushBack("one"); a.PushBack("two"); return a }, func() any { return NewSList() }},
		{"dlist", func() any { a := NewDList(); a.PushBack("one"); a.PushBack("two"); return a }, func() any { return NewDList() }},
		{"queue", func() any { a := NewQueue(); a.Push("one"); a.Push("two"); return a }, func() any { return NewQueue() }},
		{"stack", func() any { a := NewStack(); a.Push("bottom"); a.Push("top"); return a }, func() any { return NewStack() }},
		{"hash", func() any {
			a := NewHashTable(10)
			a.Insert(1, "apple")
			a.Insert(11, "banana")
			a.Insert(21, "a:b")
			return a
		}, func() any { return NewHashTable(10) }},
		{"tree", func() any {
			a := NewCompleteBinaryTree()
			for _, v := range []string{"1", "2", "3", "4", "5", "6", "7"} {
				a.Insert(v)
			}
			return a
		}, func() any { return NewCompleteBinaryTree() }},
	}
}
func TestSerialization(t *testing.T) {
	for _, tc := range fixtures() {
		t.Run(tc.name, func(t *testing.T) {
			original := tc.create()
			want, err := Pack(original)
			if err != nil {
				t.Fatal(err)
			}
			dir := t.TempDir()
			for _, format := range []string{"binary", "text"} {
				t.Run(format, func(t *testing.T) {
					path := filepath.Join(dir, format+".data")
					if format == "binary" {
						err = SaveStructureBinary(original, path)
					} else {
						err = SaveStructureText(original, path)
					}
					if err != nil {
						t.Fatal(err)
					}
					got := tc.empty()
					if format == "binary" {
						err = LoadStructureBinary(got, path)
					} else {
						err = LoadStructureText(got, path)
					}
					if err != nil {
						t.Fatal(err)
					}
					values, err := Pack(got)
					if err != nil {
						t.Fatal(err)
					}
					if !reflect.DeepEqual(want, values) {
						t.Fatalf("roundtrip mismatch: %q != %q", want, values)
					}
				})
			}
		})
	}
}
func TestEmptyStructures(t *testing.T) {
	for _, tc := range fixtures() {
		t.Run(tc.name, func(t *testing.T) {
			empty := tc.empty()
			want, _ := Pack(empty)
			for _, binary := range []bool{true, false} {
				path := filepath.Join(t.TempDir(), "empty.data")
				var err error
				if binary {
					err = SaveStructureBinary(empty, path)
				} else {
					err = SaveStructureText(empty, path)
				}
				if err != nil {
					t.Fatal(err)
				}
				restored := tc.empty()
				if binary {
					err = LoadStructureBinary(restored, path)
				} else {
					err = LoadStructureText(restored, path)
				}
				if err != nil {
					t.Fatal(err)
				}
				got, _ := Pack(restored)
				if !reflect.DeepEqual(want, got) {
					t.Fatalf("empty mismatch: %q %q", want, got)
				}
			}
		})
	}
}
func TestSerializationErrors(t *testing.T) {
	dir := t.TempDir()
	f := filepath.Join(dir, "file")
	if _, err := LoadBinary(f); err == nil {
		t.Fatal("missing binary file must fail")
	}
	if _, err := LoadText(f); err == nil {
		t.Fatal("missing text file must fail")
	}
	for _, b := range [][]byte{{0, 0}, {0xff, 0xff, 0xff, 0xff}} {
		if err := os.WriteFile(f, b, 0600); err != nil {
			t.Fatal(err)
		}
		if _, err := LoadBinary(f); err == nil {
			t.Fatal("damaged binary file accepted")
		}
	}
	for _, s := range []string{"bad", "99999999\n", "1\n\"unterminated", "1\n\"hello\"\nother"} {
		if err := os.WriteFile(f, []byte(s), 0600); err != nil {
			t.Fatal(err)
		}
		if _, err := LoadText(f); err == nil {
			t.Fatalf("damaged text accepted: %q", s)
		}
	}
	a := NewArray()
	a.PushBack("hello")
	if err := SaveStructureBinary(a, f); err != nil {
		t.Fatal(err)
	}
	if err := LoadStructureBinary(NewStack(), f); err == nil {
		t.Fatal("wrong type accepted")
	}
	target := NewArray()
	target.PushBack("existing")
	if err := LoadStructureBinary(target, f); err == nil {
		t.Fatal("nonempty destination accepted")
	}
	if target.GetString(0) != "existing" {
		t.Fatal("destination modified")
	}
	h := NewHashTable(10)
	h.Insert(1, "x")
	if err := SaveStructureBinary(h, f); err != nil {
		t.Fatal(err)
	}
	if err := LoadStructureBinary(NewHashTable(5), f); err == nil {
		t.Fatal("hash capacity mismatch accepted")
	}
	if err := SaveStructureBinary(123, f); err == nil {
		t.Fatal("unknown type accepted")
	}
}
func TestStructureOperations(t *testing.T) {
	a := NewArray()
	a.PushBack("a")
	a.Insert(0, "b")
	if a.GetSize() != 2 || a.GetString(0) != "b" {
		t.Fatal("array insert")
	}
	a.Set(1, "c")
	if a.Erase(0) != "b" || a.GetString(0) != "c" {
		t.Fatal("array erase")
	}
	s := NewSList()
	s.PushFront("b")
	s.PushBack("c")
	s.InsertAfter("b", "x")
	if s.PopFront() != "b" || s.PopBack() != "c" {
		t.Fatal("slist operations")
	}
	d := NewDList()
	d.PushFront("b")
	d.PushBack("c")
	d.InsertBefore("c", "x")
	if d.PopFront() != "b" || d.PopBack() != "c" {
		t.Fatal("dlist operations")
	}
	q := NewQueue()
	q.Push("one")
	q.Push("two")
	if q.Peek() != "one" || q.Pop() != "one" || q.Pop() != "two" {
		t.Fatal("queue order")
	}
	st := NewStack()
	st.Push("one")
	st.Push("two")
	if st.Peek() != "two" || st.Pop() != "two" || st.Pop() != "one" {
		t.Fatal("stack order")
	}
	h := NewHashTable(5)
	h.Insert(1, "x")
	h.Insert(6, "y")
	h.Insert(1, "new")
	if h.Search(1) != "new" || h.Search(6) != "y" {
		t.Fatal("hash collision")
	}
	tr := NewCompleteBinaryTree()
	for _, x := range []string{"a", "b", "c", "d"} {
		tr.Insert(x)
	}
	if !tr.IsComplete() || !tr.Search("d") || tr.Search("z") || tr.GetSize() != 4 {
		t.Fatal("tree")
	}
}
func BenchmarkArrayPushBack(b *testing.B) {
	for i := 0; i < b.N; i++ {
		a := NewArray()
		for j := 0; j < 1000; j++ {
			a.PushBack("value")
		}
		benchmarkSize = a.GetSize()
	}
}
func BenchmarkHashInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		h := NewHashTable(2003)
		for j := 0; j < 1000; j++ {
			h.Insert(j, "value")
		}
		benchmarkSize = len(h.table)
	}
}
func BenchmarkTreeInsert(b *testing.B) {
	for i := 0; i < b.N; i++ {
		tr := NewCompleteBinaryTree()
		for j := 0; j < 300; j++ {
			tr.Insert("value")
		}
		benchmarkSize = tr.GetSize()
	}
}
func BenchmarkBinarySerialization(b *testing.B) {
	values := []string{"LR3S1", "array", "0", "hello", "world"}
	path := filepath.Join(b.TempDir(), "bench.bin")
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if err := SaveBinary(values, path); err != nil {
			b.Fatal(err)
		}
	}
}
func BenchmarkTextSerialization(b *testing.B) {
	values := []string{"LR3S1", "array", "0", "hello", "world"}
	path := filepath.Join(b.TempDir(), "bench.txt")
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if err := SaveText(values, path); err != nil {
			b.Fatal(err)
		}
	}
}

var benchmarkSize int
