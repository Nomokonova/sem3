package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func isNumber(s string) bool {
	if len(s) == 0 || len(s) > 9 {
		return false
	}
	start := 0
	if s[0] == '-' {
		start = 1
	}
	if len(s)-start < 1 {
		return false
	}
	for i := start; i < len(s); i++ {
		if s[i] < '0' || s[i] > '9' {
			return false
		}
	}
	return true
}

func toIndex(s string) int {
	if !isNumber(s) {
		return -1
	}
	n, _ := strconv.Atoi(s)
	return n
}

func wordsNeeded(cmd string) int {

	need2 := []string{"PRINT", "MCREATE", "MLEN", "FPOPHEAD", "FPOPTAIL", "FGETHEAD", "FGETTAIL",
		"LPOPHEAD", "LPOPTAIL", "LGETHEAD", "LGETTAIL", "SPOP", "SPEEK", "QPOP", "QPEEK"}
	for _, c := range need2 {
		if c == cmd {
			return 2
		}
	}

	need3 := []string{"MPUSH", "MGET", "MDEL", "FPUSH", "FPUSHHEAD", "FPUSHTAIL",
		"FPOP", "FDELVAL", "FDELBEFORE", "FDELAFTER", "FGET", "FFIND",
		"LPUSH", "LPUSHHEAD", "LPUSHTAIL", "LPOP", "LDELVAL", "LDELBEFORE", "LDELAFTER", "LGET", "LFIND",
		"SPUSH", "QPUSH"}
	for _, c := range need3 {
		if c == cmd {
			return 3
		}
	}

	need4 := []string{"MINSERT", "MSET", "FPUSHBEFORE", "FPUSHAFTER", "LPUSHBEFORE", "LPUSHAFTER"}
	for _, c := range need4 {
		if c == cmd {
			return 4
		}
	}
	return -1
}

func isAddCommand(cmd string) bool {
	addCmds := []string{"MCREATE", "MPUSH", "MINSERT", "FPUSH", "FPUSHHEAD", "FPUSHTAIL",
		"LPUSH", "LPUSHHEAD", "LPUSHTAIL", "SPUSH", "QPUSH"}
	for _, c := range addCmds {
		if c == cmd {
			return true
		}
	}
	return false
}

func doArray(cmd, arg1, arg2 string, data *string) bool {
	arr := NewArray()
	words := strings.Fields(*data)
	for _, w := range words {
		arr.PushBack(w)
	}
	changed := false

	switch cmd {
	case "MCREATE":
		fmt.Println("-> empty array created")
		changed = true
	case "MPUSH":
		arr.PushBack(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "MINSERT":
		indx := toIndex(arg1)
		if indx < 0 || indx > arr.GetSize() {
			fmt.Println("Error: invalid index")
		} else {
			arr.Insert(indx, arg2)
			fmt.Printf("-> %s\n", arg2)
			changed = true
		}
	case "MGET":
		indx := toIndex(arg1)
		if indx < 0 || indx >= arr.GetSize() {
			fmt.Println("Error: invalid index")
		} else {
			fmt.Print("-> ")
			arr.Get(indx)
		}
	case "MDEL":
		indx := toIndex(arg1)
		if indx < 0 || indx >= arr.GetSize() {
			fmt.Println("Error: invalid index")
		} else {
			fmt.Printf("-> %s\n", arr.Erase(indx))
			changed = true
		}
	case "MSET":
		indx := toIndex(arg1)
		if indx < 0 || indx >= arr.GetSize() {
			fmt.Println("Error: invalid index")
		} else {
			arr.Set(indx, arg2)
			fmt.Printf("-> %s\n", arg2)
			changed = true
		}
	case "MLEN":
		fmt.Printf("-> %d\n", arr.GetSize())
	case "PRINT":
		arr.Print()
	}

	if changed {
		*data = arr.ToString()
	}
	return changed
}

func doList(cmd, arg1, arg2 string, data *string) bool {
	flist := NewSList()
	words := strings.Fields(*data)
	for _, w := range words {
		flist.PushBack(w)
	}
	changed := false

	switch cmd {
	case "FPUSHHEAD":
		flist.PushFront(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "FPUSHTAIL", "FPUSH":
		flist.PushBack(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "FPUSHBEFORE":
		flist.InsertBefore(arg1, arg2)
		changed = true
	case "FPUSHAFTER":
		flist.InsertAfter(arg1, arg2)
		changed = true
	case "FPOPHEAD", "FPOP":
		fmt.Printf("-> %s\n", flist.PopFront())
		changed = true
	case "FPOPTAIL":
		fmt.Printf("-> %s\n", flist.PopBack())
		changed = true
	case "FDELVAL":
		fmt.Printf("-> %s\n", flist.DeleteValue(arg1))
		changed = true
	case "FDELBEFORE":
		fmt.Printf("-> %s\n", flist.DeleteBefore(arg1))
		changed = true
	case "FDELAFTER":
		fmt.Printf("-> %s\n", flist.DeleteAfter(arg1))
		changed = true
	case "FGET":
		flist.GetVal(toIndex(arg1))
	case "FFIND":
		fmt.Printf("-> %d\n", flist.FindVal(arg1))
	case "FGETHEAD":
		flist.GetHead()
	case "FGETTAIL":
		flist.GetTail()
	case "PRINT":
		flist.Print()
	}

	if changed {
		*data = flist.ToString()
	}
	return changed
}

func doDoublyList(cmd, arg1, arg2 string, data *string) bool {
	dlist := NewDList()
	words := strings.Fields(*data)
	for _, w := range words {
		dlist.PushBack(w)
	}
	changed := false

	switch cmd {
	case "LPUSHHEAD":
		dlist.PushFront(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "LPUSHTAIL", "LPUSH":
		dlist.PushBack(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "LPUSHBEFORE":
		dlist.InsertBefore(arg1, arg2)
		changed = true
	case "LPUSHAFTER":
		dlist.InsertAfter(arg1, arg2)
		changed = true
	case "LPOPHEAD", "LPOP":
		fmt.Printf("-> %s\n", dlist.PopFront())
		changed = true
	case "LPOPTAIL":
		fmt.Printf("-> %s\n", dlist.PopBack())
		changed = true
	case "LDELVAL":
		fmt.Printf("-> %s\n", dlist.DeleteValue(arg1))
		changed = true
	case "LGET":
		dlist.FindInd(toIndex(arg1))
	case "LFIND":
		fmt.Printf("-> %d\n", dlist.FindVal(arg1))
	case "LGETHEAD":
		dlist.GetHead()
	case "LGETTAIL":
		dlist.GetTail()
	case "PRINT":
		dlist.Print()
	}

	if changed {
		*data = dlist.ToString()
	}
	return changed
}

func doStack(cmd, arg1 string, data *string) bool {
	st := NewStack()
	words := strings.Fields(*data)

	for i := len(words) - 1; i >= 0; i-- {
		st.Push(words[i])
	}
	changed := false

	switch cmd {
	case "SPUSH":
		st.Push(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "SPOP":
		fmt.Printf("-> %s\n", st.Pop())
		changed = true
	case "SPEEK":
		fmt.Printf("-> %s\n", st.Peek())
	case "PRINT":
		st.Print()
	}

	if changed {
		*data = st.ToString()
	}
	return changed
}

func doQueue(cmd, arg1 string, data *string) bool {
	q := NewQueue()
	words := strings.Fields(*data)
	for _, w := range words {
		q.Push(w)
	}
	changed := false

	switch cmd {
	case "QPUSH":
		q.Push(arg1)
		fmt.Printf("-> %s\n", arg1)
		changed = true
	case "QPOP":
		fmt.Printf("-> %s\n", q.Pop())
		changed = true
	case "QPEEK":
		fmt.Printf("-> %s\n", q.Peek())
	case "PRINT":
		q.Print()
	}

	if changed {
		*data = q.ToString()
	}
	return changed
}

func main() {
	var fileName, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			fileName = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}

	if fileName == "" || query == "" {
		fmt.Println("Usage: ./dbms_go --file file.data --query 'COMMAND name [args]'")
		return
	}

	parts := strings.Fields(query)
	if len(parts) < 2 {
		fmt.Println("Error: invalid query")
		return
	}
	cmd := parts[0]
	name := parts[1]

	need := wordsNeeded(cmd)
	if need == -1 {
		fmt.Printf("Error: unknown command %s\n", cmd)
		return
	}
	if len(parts) != need {
		fmt.Printf("Error: wrong number of arguments for %s\n", cmd)
		return
	}

	var arg1, arg2 string
	if need >= 3 {
		arg1 = parts[2]
	}
	if need >= 4 {
		arg2 = parts[3]
	}

	lines := NewArray()
	file, err := os.Open(fileName)
	if err == nil {
		scanner := bufio.NewScanner(file)
		for scanner.Scan() {
			line := scanner.Text()
			if line != "" {
				lines.PushBack(line)
			}
		}
		file.Close()
	}

	found := -1
	var fileType, data string
	for i := 0; i < lines.GetSize(); i++ {
		currentLine := lines.GetString(i)
		words := strings.Fields(currentLine)
		if len(words) >= 2 {
			t := words[0]
			n := words[1]
			if n == name {
				found = i
				fileType = t
				if len(words) > 2 {
					data = strings.Join(words[2:], " ")
				}
				break
			}
		}
	}

	if found == -1 && !isAddCommand(cmd) {
		fmt.Printf("Error: structure %s not found\n", name)
		return
	}

	var stype string
	if cmd == "PRINT" {
		stype = fileType
	} else {
		stype = cmd[:1]
	}

	if found != -1 && fileType != stype {
		fmt.Printf("Error: name %s is already used by another structure type\n", name)
		return
	}
	if found != -1 && cmd == "MCREATE" {
		fmt.Printf("Error: array %s already exists\n", name)
		return
	}

	changed := false
	switch stype {
	case "M":
		changed = doArray(cmd, arg1, arg2, &data)
	case "F":
		changed = doList(cmd, arg1, arg2, &data)
	case "L":
		changed = doDoublyList(cmd, arg1, arg2, &data)
	case "S":
		changed = doStack(cmd, arg1, &data)
	case "Q":
		changed = doQueue(cmd, arg1, &data)
	default:
		fmt.Println("Error: unknown structure type")
		return
	}

	if changed {
		newLine := stype + " " + name
		if data != "" {
			newLine += " " + data
		}
		if found == -1 {
			lines.PushBack(newLine)
		} else {
			lines.Set(found, newLine)
		}

		out, err := os.Create(fileName)
		if err == nil {
			for i := 0; i < lines.GetSize(); i++ {
				fmt.Fprintln(out, lines.GetString(i))
			}
			out.Close()
		}
	}
}
