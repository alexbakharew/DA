make


for test_file in `ls ../tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if !  ./benchmark < $test_file > /dev/null ; then
        echo "ERROR"
        continue
    fi
done
echo "COMPLETE"
