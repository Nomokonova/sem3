package main

import "fmt"

type Array struct {
	data     []string
	capacity int
}

func NewArray() *Array {
	return &Array{data: make([]string, 0, 10), capacity: 10}
}

func (a *Array) resize() {
	if len(a.data) < a.capacity {
		return
	}
	a.capacity *= 2
	newData := make([]string, len(a.data), a.capacity)
	copy(newData, a.data)
	a.data = newData
}

func (a *Array) Insert(index int, value string) {
	if index < 0 || index > len(a.data) {
		fmt.Println("Error")
		return
	}
	a.resize()
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = value
}

func (a *Array) PushBack(value string) {
	a.resize()
	a.data = append(a.data, value)
}

func (a *Array) Get(index int) {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Error")
		return
	}
	fmt.Println(a.data[index])
}

func (a *Array) Erase(index int) string {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Error")
		return ""
	}
	rem := a.data[index]
	a.data = append(a.data[:index], a.data[index+1:]...)
	return rem
}

func (a *Array) Set(index int, value string) {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Error")
		return
	}
	a.data[index] = value
}

func (a *Array) GetSize() int {
	return len(a.data)
}

func (a *Array) Print() {
	for _, v := range a.data {
		fmt.Print(v, " ")
	}
	fmt.Println()
}

func (a *Array) ToString() string {
	res := ""
	for i, v := range a.data {
		if i > 0 {
			res += " "
		}
		res += v
	}
	return res
}

func (a *Array) GetString(index int) string {
	if index < 0 || index >= len(a.data) {
		return ""
	}
	return a.data[index]
}
