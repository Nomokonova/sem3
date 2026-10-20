package main

import "fmt"

type QNode struct {
	value string
	next  *QNode
}

type Queue struct {
	head *QNode
	tail *QNode
}

func NewQueue() *Queue {
	return &Queue{}
}

func (q *Queue) Push(value string) {
	n := &QNode{value: value}
	if q.head == nil {
		q.head = n
		q.tail = n
	} else {
		q.tail.next = n
		q.tail = n
	}
}

func (q *Queue) Pop() string {
	if q.head == nil {
		fmt.Println("Error")
		return ""
	}
	rem := q.head.value
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	return rem
}

func (q *Queue) Peek() string {
	if q.head == nil {
		return ""
	}
	return q.head.value
}

func (q *Queue) Print() {
	if q.head == nil {
		fmt.Println("queue is empty")
		return
	}
	cur := q.head
	for cur != nil {
		fmt.Print(cur.value, " ")
		cur = cur.next
	}
	fmt.Println()
}

func (q *Queue) ToString() string {
	res := ""
	cur := q.head
	for cur != nil {
		if res != "" {
			res += " "
		}
		res += cur.value
		cur = cur.next
	}
	return res
}
