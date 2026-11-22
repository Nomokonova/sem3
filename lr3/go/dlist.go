package main

import "fmt"

type DNode struct {
	value string
	prev  *DNode
	next  *DNode
}

type DoublyLinkedList struct {
	head *DNode
	tail *DNode
}

func NewDList() *DoublyLinkedList {
	return &DoublyLinkedList{}
}

func (l *DoublyLinkedList) PushFront(value string) {
	n := &DNode{value: value, next: l.head}
	if l.head != nil {
		l.head.prev = n
	} else {
		l.tail = n
	}
	l.head = n
}

func (l *DoublyLinkedList) PushBack(value string) {
	n := &DNode{value: value, prev: l.tail}
	if l.tail != nil {
		l.tail.next = n
	} else {
		l.head = n
	}
	l.tail = n
}

func (l *DoublyLinkedList) InsertBefore(base, value string) {
	cur := l.head
	for cur != nil && cur.value != base {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("Error")
		return
	}
	n := &DNode{value: value, prev: cur.prev, next: cur}
	if cur.prev != nil {
		cur.prev.next = n
	} else {
		l.head = n
	}
	cur.prev = n
}

func (l *DoublyLinkedList) InsertAfter(base, value string) {
	cur := l.head
	for cur != nil && cur.value != base {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("Error")
		return
	}
	n := &DNode{value: value, prev: cur, next: cur.next}
	if cur.next != nil {
		cur.next.prev = n
	} else {
		l.tail = n
	}
	cur.next = n
}

func (l *DoublyLinkedList) PopFront() string {
	if l.head == nil {
		fmt.Println("Error")
		return ""
	}
	rem := l.head.value
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	return rem
}

func (l *DoublyLinkedList) PopBack() string {
	if l.tail == nil {
		fmt.Println("Error")
		return ""
	}
	rem := l.tail.value
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	return rem
}

func (l *DoublyLinkedList) DeleteValue(value string) string {
	cur := l.head
	for cur != nil && cur.value != value {
		cur = cur.next
	}
	if cur == nil {
		fmt.Println("Error")
		return ""
	}
	rem := cur.value
	if cur.prev != nil {
		cur.prev.next = cur.next
	} else {
		l.head = cur.next
	}
	if cur.next != nil {
		cur.next.prev = cur.prev
	} else {
		l.tail = cur.prev
	}
	return rem
}

func (l *DoublyLinkedList) FindVal(value string) int {
	cur := l.head
	ind := 0
	for cur != nil {
		if cur.value == value {
			return ind
		}
		cur = cur.next
		ind++
	}
	return -1
}

func (l *DoublyLinkedList) FindInd(index int) {
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

func (l *DoublyLinkedList) GetHead() {
	if l.head == nil {
		fmt.Println("list is empty")
		return
	}
	fmt.Println(l.head.value)
}

func (l *DoublyLinkedList) GetTail() {
	if l.tail == nil {
		fmt.Println("list is empty")
		return
	}
	fmt.Println(l.tail.value)
}

func (l *DoublyLinkedList) Print() {
	cur := l.head
	for cur != nil {
		fmt.Print(cur.value, " ")
		cur = cur.next
	}
	fmt.Println()
}

func (l *DoublyLinkedList) ToString() string {
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
