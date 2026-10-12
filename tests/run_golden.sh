#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd -- "${SCRIPT_DIR}/.." && pwd)"
GOLDEN_DIR="${SCRIPT_DIR}/golden"
EXECUTABLE="${1:-${PROJECT_DIR}/build-clean/oop}"

if [[ ! -x "${EXECUTABLE}" ]]; then
    echo "Golden test executable not found or not executable: ${EXECUTABLE}" >&2
    exit 2
fi

status=0

for input_file in "${GOLDEN_DIR}"/*.in; do
    scenario="${input_file%.in}"
    expected="${scenario}.out"
    actual="${scenario}.actual"

    if [[ ! -f "${expected}" ]]; then
        echo "Missing expected output: ${expected}" >&2
        status=1
        continue
    fi

    save_path="${scenario}.save.json"
    ARTNOUVEAU_SAVE_PATH="${save_path}" "${EXECUTABLE}" < "${input_file}" > "${actual}"
    normalized_actual="${actual}.normalized"
    sed 's/[[:space:]]*$//' "${actual}" > "${normalized_actual}"
    if ! diff -u "${expected}" "${normalized_actual}"; then
        echo "Golden scenario failed: $(basename "${scenario}")" >&2
        status=1
    else
        echo "Golden scenario passed: $(basename "${scenario}")"
    fi
    rm -f "${actual}" "${normalized_actual}"
    rm -f "${save_path}" "${save_path}.bak" "${save_path}.tmp"
done

exit "${status}"
