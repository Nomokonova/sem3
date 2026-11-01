package main

import "fmt"

type StackNode struct {
	value string
	next  *StackNode
}

type Stack struct {
	top *StackNode
}

func NewStack() *Stack {
	return &Stack{}
}

func (s *Stack) Push(value string) {
	s.top = &StackNode{value: value, next: s.top}
}

func (s *Stack) Pop() string {
	if s.top == nil {
		fmt.Println("Error")
		return ""
	}
	rem := s.top.value
	s.top = s.top.next
	return rem
}

func (s *Stack) Peek() string {
	if s.top == nil {
		return ""
	}
	return s.top.value
}

func (s *Stack) Print() {
	if s.top == nil {
		fmt.Println("stack is empty")
		return
	}
	cur := s.top
	for cur != nil {
		fmt.Print(cur.value, " ")
		cur = cur.next
	}
	fmt.Println()
}

func (s *Stack) ToString() string {
	res := ""
	cur := s.top
	for cur != nil {
		if res != "" {
			res += " "
		}
		res += cur.value
		cur = cur.next
	}
	return res
}
