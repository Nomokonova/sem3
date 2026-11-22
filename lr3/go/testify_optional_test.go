package main

import (
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestSerializationWithTestify(t *testing.T) {
	original := NewArray()
	original.PushBack("Привет")
	original.PushBack("hello world")
	original.PushBack("line1\nline2")
	file := filepath.Join(t.TempDir(), "array.bin")
	require.NoError(t, SaveStructureBinary(original, file))
	restored := NewArray()
	require.NoError(t, LoadStructureBinary(restored, file))
	a, err := Pack(original)
	require.NoError(t, err)
	b, err := Pack(restored)
	require.NoError(t, err)
	require.Equal(t, a, b)
}
