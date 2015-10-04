    #!/bin/bash
    
    SRC_DIR=watch
    
    cp Makefile $SRC_DIR
    cd $SRC_DIR
    make $1
    rm Makefile
    cd ..

