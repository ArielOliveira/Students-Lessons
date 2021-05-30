STUDENT_NUMBER="22042021"

touch $STUDENT_NUMBER

echo "Nascimento Joshua" > $STUDENT_NUMBER

FAILED_COUNT=$(cat result.txt | grep -c "Failed")

x=$(cat result.txt | grep -c "Passed")

FAILED_RESULT=$((FAILED_COUNT*-1))

FINAL_RESULT=$((x + FAILED_RESULT))

echo $FINAL_RESULT >> $STUDENT_NUMBER

IFS=$'\n'

ARRAY_SIZE=$(grep -Eo "\b[0-9]+\b" grades.txt | wc -w)





