for file in ./mfcc_features/*
do
    ./yourcode.out $file ${file##*/}
done