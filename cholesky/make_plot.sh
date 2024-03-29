#!/bin/sh

n_repeat=${n_repeat-5}
n_workers=${n_workers-64}
matrix_size=${matrix_size-8192}

build()
{
    mkdir -p build
    cd build
    cmake ..
    make -j
    cd ..
}

run()
{
    mkdir -p data
    for lib in redgrapes superglue quark;
    do
	truncate -s 0 data/${lib}
	for nblks in 4 8 16 32 64;
	do
	    DATA=""

            blksz=$((matrix_size / nblks))

	    for i in $(seq $n_repeat);
	    do
		echo $lib $blksz $nblks $n_workers
		OUTPUT=$(./build/$lib $blksz $nblks $n_workers || exit)
		TOTAL=$(echo $OUTPUT | grep -Po 'total \K[0-9.]*')
		echo $TOTAL
		DATA="$TOTAL $DATA"
	    done

	    echo $DATA
	    MIN=$(awk '{min = $1; for(i=1;i<=NF;i++) { if($i < min) { min = $i } } } END { printf "%f\n", min }' <<< $DATA)
	    MAX=$(awk '{max = $1; for(i=1;i<=NF;i++) { if($i > max) { max = $i } } } END { printf "%f\n", max }' <<< $DATA)
	    AVG=$(awk '{sum = 0; for(i=1;i<=NF;i++) { sum += $i } } END { printf "%f\n", sum/NF }' <<< $DATA)
	    VAR=$(awk "{ varsum = 0; for(i=1;i<=NF;i++) { varsum += (\$i - ${AVG} )*(\$i - ${AVG} ); } } END { printf \"%f\n\", varsum/NF }" <<< $DATA)
	    SIG=$(bc -l <<< "sqrt($VAR)")

	    echo "min=$MIN, max=$MAX, avg=$AVG, sigma=$SIG"
	    echo "$nblks $AVG $MIN $MAX $SIG" >> data/${lib}
	done
    done
}

plot()
{
    pushd ../thirdparty/redGrapes/
    redGrapes_commit=$(git rev-parse --short HEAD)
    popd

    TARGET_DIR="plots/${redGrapes_commit}/$(hostname)"
    mkdir -p ${TARGET_DIR}
    OUTPUT="${TARGET_DIR}/bench_cholesky_w${n_workers}_m${matrix_size}.png"
    TITLE="cholesky factorization\\\n $matrix_size x $matrix_size matrix of 64-bit float\\\n $n_workers workers \\\nhost: $(hostname)\\\nredGrapes: \#${redGrapes_commit}"
    LABEL_X="tiling factor (#tiles^{0.5})"
    LABEL_Y="runtime (ms)"

    . ../plot.sh <<< "data/quark Quark #86C4FF #006DD5
data/superglue SuperGlue #88F176 #20D500
data/redgrapes RedGrapes #C976F1 #670496"
}

build
run
plot


