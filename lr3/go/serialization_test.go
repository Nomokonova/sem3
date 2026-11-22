package main

import (
	"encoding/binary"
	"os"
	"path/filepath"
	"reflect"
	"strings"
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

// Дополнительные проверки сериализации и обработки некорректных файлов.

func TestSerializerBinaryInvalidInput(t *testing.T) {
	cases := []struct {
		name string
		data []byte
	}{
		{"empty", nil},
		{"incomplete_count", []byte{1, 0}},
		{"too_many_items", []byte{0x41, 0x42, 0x0f, 0x00}}, // 1000001
		{"missing_string_length", []byte{1, 0, 0, 0}},
		{"incomplete_string_length", []byte{1, 0, 0, 0, 2, 0}},
		{"too_long_string", []byte{1, 0, 0, 0, 0x41, 0x42, 0x0f, 0x00}},
		{"truncated_string", []byte{1, 0, 0, 0, 4, 0, 0, 0, 'A'}},
		{"extra_bytes", []byte{0, 0, 0, 0, 'X'}},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), "invalid.bin")
			if err := os.WriteFile(path, tc.data, 0600); err != nil {
				t.Fatal(err)
			}
			if _, err := LoadBinary(path); err == nil {
				t.Fatal("expected error")
			}
		})
	}
}

func TestSerializerTextInvalidInput(t *testing.T) {
	cases := []struct{ name, data string }{
		{"empty", ""},
		{"bad_count", "nope\n"},
		{"too_many_items", "1000001\n"},
		{"missing_string", "1\n"},
		{"bad_quote", "1\nwrong\n"},
		{"unfinished_quote", "1\n\"hello"},
		{"extra_text", "0\nextra"},
		{"long_string", "1\n\"" + strings.Repeat("x", maxString+1) + "\"\n"},
	}
	for _, tc := range cases {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), "invalid.txt")
			if err := os.WriteFile(path, []byte(tc.data), 0600); err != nil {
				t.Fatal(err)
			}
			if _, err := LoadText(path); err == nil {
				t.Fatal("expected error")
			}
		})
	}
}

func TestSerializerOversizedAndInvalidDestinations(t *testing.T) {
	tooMany := make([]string, maxItems+1)
	tooLong := []string{strings.Repeat("x", maxString+1)}
	for _, tc := range []struct {
		name   string
		values []string
	}{
		{"too_many", tooMany},
		{"string_too_long", tooLong},
	} {
		t.Run(tc.name, func(t *testing.T) {
			if err := SaveBinary(tc.values, filepath.Join(t.TempDir(), "data.bin")); err == nil {
				t.Fatal("binary must reject oversized input")
			}
			if err := SaveText(tc.values, filepath.Join(t.TempDir(), "data.txt")); err == nil {
				t.Fatal("text must reject oversized input")
			}
		})
	}
	path := filepath.Join(t.TempDir(), "no_such_folder", "file")
	if err := SaveBinary([]string{"ok"}, path); err == nil {
		t.Fatal("expected binary open error")
	}
	if err := SaveText([]string{"ok"}, path); err == nil {
		t.Fatal("expected text open error")
	}
}

func TestSerializerSpecialStrings(t *testing.T) {
	values := []string{"", "spaces and words", "quoted: \"hi\"", `C:\\Temp\\file`, "строка\nновая", "é"}
	for _, tc := range []struct {
		name string
		save func([]string, string) error
		load func(string) ([]string, error)
	}{
		{"binary", SaveBinary, LoadBinary},
		{"text", SaveText, LoadText},
	} {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(t.TempDir(), "data")
			if err := tc.save(values, path); err != nil {
				t.Fatal(err)
			}
			got, err := tc.load(path)
			if err != nil {
				t.Fatal(err)
			}
			if !reflect.DeepEqual(got, values) {
				t.Fatalf("got %#v, want %#v", got, values)
			}
		})
	}
}

func TestSerializerTextWhitespaceAndEscape(t *testing.T) {
	path := filepath.Join(t.TempDir(), "quoted.txt")
	input := "1\n  \"a\\\"b\\\\c\" \n\t"
	if err := os.WriteFile(path, []byte(input), 0600); err != nil {
		t.Fatal(err)
	}
	got, err := LoadText(path)
	if err != nil {
		t.Fatal(err)
	}
	if !reflect.DeepEqual(got, []string{"a\"b\\c"}) {
		t.Fatalf("unexpected %q", got)
	}
}

func TestSerializerBinaryLittleEndian(t *testing.T) {
	path := filepath.Join(t.TempDir(), "le.bin")
	if err := SaveBinary([]string{"a"}, path); err != nil {
		t.Fatal(err)
	}
	b, err := os.ReadFile(path)
	if err != nil {
		t.Fatal(err)
	}
	if len(b) != 9 || binary.LittleEndian.Uint32(b[:4]) != 1 || binary.LittleEndian.Uint32(b[4:8]) != 1 || b[8] != 'a' {
		t.Fatalf("unexpected binary bytes: %v", b)
	}
}
