source=main.cpp
bin=${source%.*}


if ! python3 checker.py ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

path = './tests/'
for test_file in `ls tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if !  ./src/lab7 < $test_file > "${answer_file}.pl" ; then
        echo "ERROR"
        continue
    fi

    if ! diff -u "${answer_file}.txt"  "${answer_file}.pl" > /dev/null ; then
        echo "Failed"
    else
        echo "OK"
    fi 
done  
