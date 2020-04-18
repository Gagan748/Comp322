

EXEC= dining-p
SEATS=$1


for((i=0; $i < $SEATS; i+=1))
do
	echo "./dining-p $SEATS $i"
done

./dining-p $SEATS
