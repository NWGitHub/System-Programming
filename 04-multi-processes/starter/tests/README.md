# Visible Checks

Run the local visible check with:

```bash
./scripts/test.sh
```

What it checks:
- the project builds cleanly
- the child reports updated global/heap/stack values
- the parent reports child exit status and unchanged parent values
- the parent confirms address-space isolation

The starter code is expected to fail until the TODO sections are implemented.