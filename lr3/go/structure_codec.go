package main

import (
	"errors"
	"strconv"
	"strings"
)

const version = "LR3S1"

func header(kind string, capacity int) []string {
	return []string{version, kind, strconv.Itoa(capacity)}
}
func checkHeader(data []string, kind string) error {
	if len(data) < 3 || data[0] != version || data[1] != kind {
		return errors.New("wrong structure type/version")
	}
	if kind != "hash" && data[2] != "0" {
		return errors.New("invalid metadata")
	}
	return nil
}

func Pack(object any) ([]string, error) {
	switch o := object.(type) {
	case *Array:
		out := header("array", 0)
		return append(out, o.data...), nil
	case *SinglyLinkedList:
		out := header("slist", 0)
		for n := o.head; n != nil; n = n.next {
			out = append(out, n.value)
		}
		return out, nil
	case *DoublyLinkedList:
		out := header("dlist", 0)
		for n := o.head; n != nil; n = n.next {
			out = append(out, n.value)
		}
		return out, nil
	case *Queue:
		out := header("queue", 0)
		for n := o.head; n != nil; n = n.next {
			out = append(out, n.value)
		}
		return out, nil
	case *Stack:
		out := header("stack", 0)
		for n := o.top; n != nil; n = n.next {
			out = append(out, n.value)
		}
		return out, nil
	case *HashTable:
		out := header("hash", o.capacity)
		return append(out, o.table...), nil
	case *CompleteBinaryTree:
		return append(header("tree", 0), o.Values()...), nil
	default:
		return nil, errors.New("unsupported structure")
	}
}

func Unpack(data []string, object any) error {
	var kind string
	switch object.(type) {
	case *Array:
		kind = "array"
	case *SinglyLinkedList:
		kind = "slist"
	case *DoublyLinkedList:
		kind = "dlist"
	case *Queue:
		kind = "queue"
	case *Stack:
		kind = "stack"
	case *HashTable:
		kind = "hash"
	case *CompleteBinaryTree:
		kind = "tree"
	default:
		return errors.New("unsupported structure")
	}
	if err := checkHeader(data, kind); err != nil {
		return err
	}
	values := data[3:]
	switch o := object.(type) {
	case *Array:
		if o.GetSize() != 0 {
			return errors.New("destination not empty")
		}
		for _, v := range values {
			o.PushBack(v)
		}
	case *SinglyLinkedList:
		if o.head != nil {
			return errors.New("destination not empty")
		}
		for _, v := range values {
			o.PushBack(v)
		}
	case *DoublyLinkedList:
		if o.head != nil {
			return errors.New("destination not empty")
		}
		for _, v := range values {
			o.PushBack(v)
		}
	case *Queue:
		if o.head != nil {
			return errors.New("destination not empty")
		}
		for _, v := range values {
			o.Push(v)
		}
	case *Stack:
		if o.top != nil {
			return errors.New("destination not empty")
		}
		for i := len(values) - 1; i >= 0; i-- {
			o.Push(values[i])
		}
	case *HashTable:
		cap, err := strconv.Atoi(data[2])
		if err != nil || cap <= 0 || cap > maxItems || cap != o.capacity || len(values) != cap {
			return errors.New("invalid hash capacity")
		}
		for _, v := range o.table {
			if v != "" {
				return errors.New("destination not empty")
			}
		}
		for _, entry := range values {
			if entry == "" {
				continue
			}
			k, _, ok := strings.Cut(entry, ":")
			if !ok {
				return errors.New("invalid hash entry")
			}
			if _, err := strconv.Atoi(k); err != nil {
				return errors.New("invalid hash key")
			}
		}
		copy(o.table, values)
	case *CompleteBinaryTree:
		if o.root != nil {
			return errors.New("destination not empty")
		}
		for _, v := range values {
			o.Insert(v)
		}
	}
	return nil
}
func SaveStructureBinary(object any, path string) error {
	data, err := Pack(object)
	if err != nil {
		return err
	}
	return SaveBinary(data, path)
}
func SaveStructureText(object any, path string) error {
	data, err := Pack(object)
	if err != nil {
		return err
	}
	return SaveText(data, path)
}
func LoadStructureBinary(object any, path string) error {
	data, err := LoadBinary(path)
	if err != nil {
		return err
	}
	return Unpack(data, object)
}
func LoadStructureText(object any, path string) error {
	data, err := LoadText(path)
	if err != nil {
		return err
	}
	return Unpack(data, object)
}
