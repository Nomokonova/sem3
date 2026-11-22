package main

import "fmt"

type SNode struct {
	value string
	next  *SNode
}

type SinglyLinkedList struct {
	head *SNode
}

func NewSList() *SinglyLinkedList {
	return &SinglyLinkedList{}
}

func (l *SinglyLinkedList) PushFront(value string) {
	l.head = &SNode{value: value, next: l.head}
}

func (l *SinglyLinkedList) PushBack(value string) {
	n := &SNode{value: value}
	if l.head == nil {
		l.head = n
		return
	}
	cur := l.head
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = n
}

func (l *SinglyLinkedList) InsertBefore(base, value string) {
	if l.head == nil {
		fmt.Println("Error")
		return
	}
	if l.head.value == base {
		l.PushFront(value)
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.value != base {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("Error")
		return
	}
	cur.next = &SNode{value: value, next: cur.next}
}

func (l *SinglyLinkedList) InsertAfter(base, value string) {
	cur := l.head
	for cur != nil && cur.value != base {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("Error")
		return
	}
	cur.next = &SNode{value: value, next: cur.next}
}

func (l *SinglyLinkedList) PopFront() string {
	if l.head == nil {
		fmt.Println("Error")
		return ""
	}
	rem := l.head.value
	l.head = l.head.next
	return rem
}

func (l *SinglyLinkedList) PopBack() string {
	if l.head == nil {
		fmt.Println("Error")
		return ""
	}
	if l.head.next == nil {
		rem := l.head.value
		l.head = nil
		return rem
	}
	cur := l.head
	for cur.next.next != nil {
		cur = cur.next
	}
	rem := cur.next.value
	cur.next = nil
	return rem
}

func (l *SinglyLinkedList) DeleteBefore(base string) string {
	if l.head == nil || l.head.value == base {
		fmt.Println("Error")
		return ""
	}
	if l.head.next != nil && l.head.next.value == base {
		return l.PopFront()
	}
	cur := l.head
	for cur.next.next != nil && cur.next.next.value != base {
		cur = cur.next
	}
	if cur.next.next == nil {
		fmt.Println("Error")
		return ""
	}
	rem := cur.next.value
	cur.next = cur.next.next
	return rem
}

func (l *SinglyLinkedList) DeleteAfter(base string) string {
	cur := l.head
	for cur != nil && cur.value != base {
		cur = cur.next
	}
	if cur == nil || cur.next == nil {
		fmt.Println("Error")
		return ""
	}
	rem := cur.next.value
	cur.next = cur.next.next
	return rem
}

func (l *SinglyLinkedList) DeleteValue(value string) string {
	if l.head == nil {
		fmt.Println("Error")
		return ""
	}
	if l.head.value == value {
		return l.PopFront()
	}
	cur := l.head
	for cur.next != nil && cur.next.value != value {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Println("Error")
		return ""
	}
	rem := cur.next.value
	cur.next = cur.next.next
	return rem
}

func (l *SinglyLinkedList) FindVal(val string) int {
	cur := l.head
	ind := 0
	for cur != nil {
		if cur.value == val {
			return ind
		}
		cur = cur.next
		ind++
	}
	return -1
}

func (l *SinglyLinkedList) GetVal(index int) {
	if index < 0 {
		fmt.Println("Error")
		return
	}
	cur := l.head
	for i := 0; i < index; i++ {
		if cur == nil {
			fmt.Println("Error")
			return
		}
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("Error")
		return
	}
	fmt.Println(cur.value)
}

func (l *SinglyLinkedList) GetHead() {
	if l.head == nil {
		fmt.Println("list is empty")
		return
	}
	fmt.Println(l.head.value)
}

func (l *SinglyLinkedList) GetTail() {
	if l.head == nil {
		fmt.Println("list is empty")
		return
	}
	cur := l.head
	for cur.next != nil {
		cur = cur.next
	}
	fmt.Println(cur.value)
}

func (l *SinglyLinkedList) Print() {
	cur := l.head
	for cur != nil {
		fmt.Print(cur.value, " ")
		cur = cur.next
	}
	fmt.Println()
}

func (l *SinglyLinkedList) ToString() string {
	res := ""
	cur := l.head
	for cur != nil {
		if res != "" {
			res += " "
		}
		res += cur.value
		cur = cur.next
	}
	return res
}
