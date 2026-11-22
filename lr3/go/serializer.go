package main

import (
	"bufio"
	"encoding/binary"
	"errors"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

const maxItems = 1_000_000
const maxString = 1_000_000

func validateValues(values []string) error {
	if len(values) > maxItems {
		return errors.New("too many elements")
	}
	for _, s := range values {
		if len(s) > maxString {
			return errors.New("string too long")
		}
	}
	return nil
}
func SaveBinary(values []string, path string) (err error) {
	if err = validateValues(values); err != nil {
		return err
	}
	f, err := os.Create(path)
	if err != nil {
		return err
	}
	defer func() {
		if e := f.Close(); err == nil {
			err = e
		}
	}()
	w := bufio.NewWriter(f)
	if err = binary.Write(w, binary.LittleEndian, uint32(len(values))); err != nil {
		return err
	}
	for _, s := range values {
		if err = binary.Write(w, binary.LittleEndian, uint32(len(s))); err != nil {
			return err
		}
		if _, err = io.WriteString(w, s); err != nil {
			return err
		}
	}
	return w.Flush()
}
func LoadBinary(path string) ([]string, error) {
	f, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	r := bufio.NewReader(f)
	var count uint32
	if err = binary.Read(r, binary.LittleEndian, &count); err != nil {
		return nil, err
	}
	if count > maxItems {
		return nil, errors.New("too many elements")
	}
	out := make([]string, 0, count)
	for i := uint32(0); i < count; i++ {
		var n uint32
		if err = binary.Read(r, binary.LittleEndian, &n); err != nil {
			return nil, err
		}
		if n > maxString {
			return nil, errors.New("string too long")
		}
		b := make([]byte, n)
		if _, err = io.ReadFull(r, b); err != nil {
			return nil, err
		}
		out = append(out, string(b))
	}
	if _, err = r.ReadByte(); err != io.EOF {
		if err == nil {
			return nil, errors.New("extra data")
		}
		return nil, err
	}
	return out, nil
}

func quoteCPP(s string) string {
	var b strings.Builder
	b.WriteByte('"')
	for i := 0; i < len(s); i++ {
		if s[i] == '"' || s[i] == '\\' {
			b.WriteByte('\\')
		}
		b.WriteByte(s[i])
	}
	b.WriteByte('"')
	return b.String()
}
func SaveText(values []string, path string) (err error) {
	if err = validateValues(values); err != nil {
		return err
	}
	f, err := os.Create(path)
	if err != nil {
		return err
	}
	defer func() {
		if e := f.Close(); err == nil {
			err = e
		}
	}()
	w := bufio.NewWriter(f)
	if _, err = fmt.Fprintf(w, "%d\n", len(values)); err != nil {
		return err
	}
	for _, s := range values {
		if _, err = io.WriteString(w, quoteCPP(s)+"\n"); err != nil {
			return err
		}
	}
	return w.Flush()
}
func readQuoted(r *bufio.Reader) (string, error) {
	for {
		b, err := r.ReadByte()
		if err != nil {
			return "", err
		}
		if b == '"' {
			break
		}
		if b != ' ' && b != '\n' && b != '\t' && b != '\r' {
			return "", errors.New("expected quote")
		}
	}
	var b strings.Builder
	escaped := false
	for {
		c, err := r.ReadByte()
		if err != nil {
			return "", err
		}
		if escaped {
			b.WriteByte(c)
			escaped = false
			continue
		}
		if c == '\\' {
			escaped = true
			continue
		}
		if c == '"' {
			return b.String(), nil
		}
		b.WriteByte(c)
		if b.Len() > maxString {
			return "", errors.New("string too long")
		}
	}
}
func LoadText(path string) ([]string, error) {
	f, err := os.Open(path)
	if err != nil {
		return nil, err
	}
	defer f.Close()
	r := bufio.NewReader(f)
	line, err := r.ReadString('\n')
	if err != nil {
		return nil, err
	}
	line = strings.TrimSpace(line)
	n, err := strconv.ParseUint(line, 10, 32)
	if err != nil {
		return nil, err
	}
	if n > maxItems {
		return nil, errors.New("too many elements")
	}
	out := make([]string, 0, n)
	for i := uint64(0); i < n; i++ {
		s, err := readQuoted(r)
		if err != nil {
			return nil, err
		}
		if len(s) > maxString {
			return nil, errors.New("string too long")
		}
		out = append(out, s)
	}
	for {
		c, err := r.ReadByte()
		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, err
		}
		if c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != '\v' && c != '\f' {
			return nil, errors.New("extra data")
		}
	}
	return out, nil
}
