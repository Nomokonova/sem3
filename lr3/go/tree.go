package main

import "fmt"

type TNode struct {
	value       string
	left, right *TNode
}
type CompleteBinaryTree struct {
	root *TNode
	size int
}

func NewCompleteBinaryTree() *CompleteBinaryTree { return &CompleteBinaryTree{} }
func (t *CompleteBinaryTree) Insert(value string) {
	node := &TNode{value: value}
	if t.root == nil {
		t.root = node
		t.size++
		return
	}
	q := []*TNode{t.root}
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n.left == nil {
			n.left = node
			t.size++
			return
		}
		q = append(q, n.left)
		if n.right == nil {
			n.right = node
			t.size++
			return
		}
		q = append(q, n.right)
	}
}
func (t *CompleteBinaryTree) Search(value string) bool {
	var walk func(*TNode) bool
	walk = func(n *TNode) bool { return n != nil && (n.value == value || walk(n.left) || walk(n.right)) }
	return walk(t.root)
}
func (t *CompleteBinaryTree) IsComplete() bool {
	if t.root == nil {
		return true
	}
	q := []*TNode{t.root}
	empty := false
	for len(q) > 0 {
		n := q[0]
		q = q[1:]
		if n.left != nil {
			if empty {
				return false
			}
			q = append(q, n.left)
		} else {
			empty = true
		}
		if n.right != nil {
			if empty {
				return false
			}
			q = append(q, n.right)
		} else {
			empty = true
		}
	}
	return true
}
func (t *CompleteBinaryTree) GetSize() int { return t.size }
func (t *CompleteBinaryTree) Values() []string {
	result := []string{}
	if t.root == nil {
		return result
	}
	q := []*TNode{t.root}
	for i := 0; i < len(q); i++ {
		n := q[i]
		result = append(result, n.value)
		if n.left != nil {
			q = append(q, n.left)
		}
		if n.right != nil {
			q = append(q, n.right)
		}
	}
	return result
}
func (t *CompleteBinaryTree) Print() {
	for _, v := range t.Values() {
		fmt.Println(v)
	}
}
func (t *CompleteBinaryTree) ToString() string {
	res := ""
	for _, v := range t.Values() {
		if res != "" {
			res += " "
		}
		res += v
	}
	return res
}
