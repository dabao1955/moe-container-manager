#!/bin/bash
source global.sh

# This will set $TEST_ROOT
export TEST_ROOT=$(pwd)

DESCRIPTION="This is a test script that runs all test scripts."
echo -e "${BASE}Running $0"
echo -e "${BASE}Description:\n${CYAN} ${DESCRIPTION}"
printf "${CLEAR}"
sleep 1

# This will set $TMPDIR
cd ${TEST_ROOT}
source init-root-test.sh
check_if_succeed $?

# Do all tests
cd ${TEST_ROOT}
for i in $(ls root/*.sh); do
    cd ${TEST_ROOT}
    source $i
    check_if_succeed $?
done

cd ${TMPDIR}
rm ruri
wget -O - https://github.com/Moe-hacker/ruri/raw/refs/heads/main/get-ruri.sh | bash -s -- -s
check_if_succeed $?

# Check for released version
cd ${TEST_ROOT}
for i in $(ls root/*.sh); do
    cd ${TEST_ROOT}
    source $i
    check_if_succeed $?
done

# Clean up
cd ${TEST_ROOT}
source clean.sh

echo -e "${BASE}Passed all root tests!${CLEAR}"
