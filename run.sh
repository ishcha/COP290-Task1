
for i in {1..5}
do
	for file in ./mfcc_features/*
	do
	    ./yourcode.out $file ./outputs2/${file##*/}
	done
done