package main

import (
	"fmt"
	"strconv"
	"strings"
)

type HashTable struct {
	table    []string
	capacity int
}

func NewHashTable(capacity int) *HashTable {
	if capacity <= 0 {
		panic("capacity must be positive")
	}
	return &HashTable{table: make([]string, capacity), capacity: capacity}
}
func (h *HashTable) hashFunc(key int) int { return (key%h.capacity + h.capacity) % h.capacity }
func (h *HashTable) Insert(key int, value string) int {
	index := h.hashFunc(key)
	for steps := 0; steps < h.capacity; steps++ {
		entry := h.table[index]
		if entry == "" {
			h.table[index] = strconv.Itoa(key) + ":" + value
			return steps
		}
		k, _, ok := strings.Cut(entry, ":")
		if !ok {
			return -1
		}
		old, err := strconv.Atoi(k)
		if err != nil {
			return -1
		}
		if old == key {
			h.table[index] = strconv.Itoa(key) + ":" + value
			return steps
		}
		index = (index + 1) % h.capacity
	}
	return -1
}
func (h *HashTable) Search(key int) string {
	index := h.hashFunc(key)
	for steps := 0; steps < h.capacity; steps++ {
		entry := h.table[index]
		if entry == "" {
			return ""
		}
		k, v, ok := strings.Cut(entry, ":")
		if !ok {
			return ""
		}
		old, err := strconv.Atoi(k)
		if err != nil {
			return ""
		}
		if old == key {
			return v
		}
		index = (index + 1) % h.capacity
	}
	return ""
}
func (h *HashTable) Print() {
	for i, e := range h.table {
		if e != "" {
			fmt.Printf("[%d]: %s\n", i, e)
		}
	}
}
func (h *HashTable) ToString() string {
	s := []string{}
	for _, e := range h.table {
		if e != "" {
			s = append(s, e)
		}
	}
	return strings.Join(s, " ")
}

func (h *HashTable) Remove(key int) bool {
	index := h.hashFunc(key)

	for steps := 0; steps < h.capacity; steps++ {
		entry := h.table[index]
		if entry == "" {
			return false
		}
		k, _, ok := strings.Cut(entry, ":")
		if !ok {
			return false
		}
		existingKey, err := strconv.Atoi(k)
		if err != nil {
			return false
		}
		if existingKey == key {
			h.table[index] = ""
			next := (index + 1) % h.capacity
			for h.table[next] != "" {
				displaced := h.table[next]
				h.table[next] = ""
				k, value, _ := strings.Cut(displaced, ":")
				displacedKey, _ := strconv.Atoi(k)
				h.Insert(displacedKey, value)
				next = (next + 1) % h.capacity
			}
			return true
		}
		index = (index + 1) % h.capacity
	}
	return false
}
