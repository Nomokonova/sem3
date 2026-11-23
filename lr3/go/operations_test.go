package main

import "testing"

func TestArrayExtra(t *testing.T) {
	a := NewArray()
	a.Insert(-1, "bad")
	a.Insert(1, "bad")
	a.Get(-1)
	a.Set(0, "bad")
	a.Erase(1)
	a.GetString(-1)
	for i := 0; i < 25; i++ {
		a.PushBack("x")
	}
	a.Insert(2, "new")
	a.Get(2)
	a.Set(2, "set")
	a.Print()
	if a.ToString() == "" {
		t.Fatal("empty")
	}
	if a.Erase(2) != "set" {
		t.Fatal("erase")
	}
	if a.GetSize() != 25 {
		t.Fatal("size")
	}
	a.GetString(500)
}
func TestSinglyListExtra(t *testing.T) {
	l := NewSList()
	l.PopFront()
	l.PopBack()
	l.DeleteBefore("x")
	l.DeleteAfter("x")
	l.DeleteValue("x")
	l.GetHead()
	l.GetTail()
	l.GetVal(-1)
	l.GetVal(2)
	l.InsertBefore("x", "y")
	l.InsertAfter("x", "y")
	l.PushFront("a")
	l.PushBack("b")
	l.PushBack("c")
	l.PushBack("d")
	l.InsertBefore("a", "z")
	l.InsertBefore("c", "before")
	l.InsertBefore("missing", "x")
	l.InsertAfter("b", "after")
	l.InsertAfter("missing", "x")
	if l.FindVal("a") < 0 || l.FindVal("missing") != -1 {
		t.Fatal("find")
	}
	l.GetVal(0)
	l.GetVal(99)
	l.GetHead()
	l.GetTail()
	l.Print()
	if l.ToString() == "" {
		t.Fatal("string")
	}
	if l.DeleteAfter("after") != "before" {
		t.Fatal("delete after")
	}
	if l.DeleteBefore("b") != "a" {
		t.Fatal("delete before")
	}
	l.DeleteBefore("missing")
	l.DeleteAfter("missing")
	l.DeleteValue("missing")
	l.DeleteValue("z")
	l.DeleteValue("after")
	l.DeleteValue("b")
	l.PopBack()
	l.PopFront()
	l.PopBack()
	one := NewSList()
	one.PushBack("single")
	if one.PopBack() != "single" {
		t.Fatal("single")
	}
	one.PushBack("first")
	one.PushBack("second")
	if one.DeleteBefore("second") != "first" {
		t.Fatal("first")
	}
}
func TestDoublyListExtra(t *testing.T) {
	l := NewDList()
	l.PopFront()
	l.PopBack()
	l.DeleteValue("missing")
	l.FindInd(-1)
	l.GetHead()
	l.GetTail()
	l.Print()
	l.InsertBefore("missing", "x")
	l.InsertAfter("missing", "x")
	l.PushFront("a")
	l.PushBack("b")
	l.PushBack("c")
	l.InsertBefore("a", "z")
	l.InsertBefore("c", "before")
	l.InsertAfter("c", "d")
	l.InsertAfter("a", "after")
	l.InsertBefore("missing", "x")
	l.InsertAfter("missing", "x")
	if l.FindVal("a") < 0 || l.FindVal("missing") != -1 {
		t.Fatal("find")
	}
	l.FindInd(0)
	l.FindInd(99)
	l.GetHead()
	l.GetTail()
	l.Print()
	if l.ToString() == "" {
		t.Fatal("string")
	}
	if l.DeleteValue("after") != "after" {
		t.Fatal("delete middle")
	}
	l.DeleteValue("z")
	l.DeleteValue("d")
	l.DeleteValue("missing")
	l.PopFront()
	l.PopBack()
	l.PopFront()
	l.PopBack()
	one := NewDList()
	one.PushFront("x")
	if one.PopFront() != "x" {
		t.Fatal("single front")
	}
	one.PushBack("y")
	if one.PopBack() != "y" {
		t.Fatal("single back")
	}
}
func TestQueueStackExtra(t *testing.T) {
	q := NewQueue()
	q.Pop()
	q.Peek()
	q.Print()
	q.ToString()
	q.Push("a")
	q.Push("b")
	q.Print()
	if q.ToString() != "a b" {
		t.Fatal("queue string")
	}
	q.Pop()
	q.Pop()
	q.Print()
	s := NewStack()
	s.Pop()
	s.Peek()
	s.Print()
	s.ToString()
	s.Push("a")
	s.Push("b")
	s.Print()
	if s.ToString() != "b a" {
		t.Fatal("stack string")
	}
	s.Pop()
	s.Pop()
	s.Print()
}
func TestHashTreeExtra(t *testing.T) {
	h := NewHashTable(2)
	if h.Insert(1, "a") < 0 || h.Insert(3, "b") < 0 {
		t.Fatal("hash")
	}
	if h.Insert(5, "c") != -1 {
		t.Fatal("full hash")
	}
	if h.Search(5) != "" {
		t.Fatal("missing hash")
	}
	h.Print()
	if h.ToString() == "" {
		t.Fatal("string")
	}
	h2 := NewHashTable(5)
	h2.Insert(-1, "negative")
	if h2.Search(-1) != "negative" {
		t.Fatal("negative hash")
	}
	h2.Search(7)
	empty := NewCompleteBinaryTree()
	if !empty.IsComplete() || empty.Search("x") || len(empty.Values()) != 0 {
		t.Fatal("empty tree")
	}
	empty.Print()
	empty.ToString()
	tr := NewCompleteBinaryTree()
	for _, s := range []string{"a", "b", "c", "d"} {
		tr.Insert(s)
	}
	tr.Print()
	if tr.ToString() == "" {
		t.Fatal("tree string")
	}
	tr.root.left.left = nil
	tr.root.right.left = &TNode{value: "gap"}
	if tr.IsComplete() {
		t.Fatal("broken tree considered complete")
	}
}
func TestHashTableRemove(t *testing.T) {
	t.Run("Remove existing key", func(t *testing.T) {
		ht := NewHashTable(5)

		ht.Insert(1, "A")
		ht.Insert(2, "B")

		if !ht.Remove(1) {
			t.Fatal("Failed to remove existing key")
		}

		if ht.Search(1) != "" {
			t.Fatal("Deleted key still exists")
		}

		if ht.Search(2) != "B" {
			t.Fatal("Other key was affected")
		}
	})

	t.Run("Remove with collisions", func(t *testing.T) {
		ht := NewHashTable(5)

		ht.Insert(1, "A")
		ht.Insert(6, "B")
		ht.Insert(11, "C")

		if !ht.Remove(1) {
			t.Fatal("Failed to remove key")
		}

		if ht.Search(6) != "B" {
			t.Fatal("Key 6 lost after removal")
		}

		if ht.Search(11) != "C" {
			t.Fatal("Key 11 lost after removal")
		}

		if !ht.Remove(6) {
			t.Fatal("Failed to remove key 6")
		}
	})

	t.Run("Remove missing key", func(t *testing.T) {
		ht := NewHashTable(5)

		ht.Insert(1, "A")

		if ht.Remove(99) {
			t.Fatal("Removed nonexistent key")
		}

		if !ht.Remove(1) {
			t.Fatal("Failed to remove key")
		}

		if ht.Remove(1) {
			t.Fatal("Removed the same key twice")
		}
	})

	t.Run("Remove from full table", func(t *testing.T) {
		ht := NewHashTable(3)

		ht.Insert(0, "A")
		ht.Insert(3, "B")
		ht.Insert(6, "C")

		if ht.Remove(99) {
			t.Fatal("Removed missing key from full table")
		}

		if !ht.Remove(0) {
			t.Fatal("Failed to remove existing key")
		}

		if ht.Search(3) != "B" || ht.Search(6) != "C" {
			t.Fatal("Collision chain broken")
		}
	})

	t.Run("Remove from empty table", func(t *testing.T) {
		ht := NewHashTable(5)

		if ht.Remove(1) {
			t.Fatal("Removed key from empty table")
		}
	})
}
