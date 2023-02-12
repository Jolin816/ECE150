#include  "geesespotter_lib.h"
#include "geesespotter.h"

char * createBoard(std::size_t xdim, std::size_t ydim) {
    char *board{new char[xdim*ydim]};
    for(int i=0;i<xdim*ydim;++i) {
        board[i]=0;
    }
    return board;
}

void cleanBoard(char * board) {
    delete[] board;
    board = nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim) {
    for( std::size_t i {0}; i < ydim; ++i){
        for(std::size_t j {0}; j < xdim; ++j){
            if((board[i*xdim+j]& markedBit()) == markedBit()) {
                std::cout << 'M';
            }
            else if((board[i*xdim+j]& hiddenBit()) == hiddenBit()) {
                std::cout << '*';
            }
            else {
                std::cout << (board[i*xdim+j] & valueMask());
            }
        }
        std::cout<<std::endl;
    }
}

void hideBoard(char * board, std::size_t xdim, std::size_t ydim) {
    for(int i=0;i<xdim*ydim;++i) {
        board[i] |= hiddenBit();
    }
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    if((board[ydim*yloc+xloc] & hiddenBit()) == hiddenBit()) {
        if((board[xdim*yloc+xloc] & markedBit()) != markedBit()) {
            board[xdim*yloc+xloc] |= markedBit();
        }
        else {
            board[xdim*yloc+xloc] &= ~markedBit();
        }
        return 0;
    }
    else {
        return 2;
    }
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim) {
    for(int i=0;i<xdim*ydim;++i) {
        int numberofgeese{0};
        if((board[i] & valueMask()) != 9) {
            //up
            if(i>=xdim) {
                if((board[i-xdim] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //down
            if(i<(xdim*ydim-xdim)) {
                if((board[i+xdim] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //right
            if((i+1)%xdim!=0) {
                if((board[i+1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //left
            if(i%xdim!=0) {
                if((board[i-1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //upleft
            if((i>=xdim) && (i%xdim!=0)) {
                if((board[i-xdim-1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //upright
            if((i>=xdim) && ((i+1)%xdim!=0)) {
                if((board[i-xdim+1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //downleft
            if((i<(xdim*ydim-xdim)) && (i%xdim!=0)) {
                if((board[i+xdim-1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            //downright
            if((i<(xdim*ydim-xdim)) && ((i+1)%xdim!=0)) {
                if((board[i+xdim+1] & valueMask())==9) {
                    numberofgeese++;
                }
            }
            board[i] |= numberofgeese;
        }
    }
    return;
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    if((board[xdim*yloc+xloc]&markedBit())==markedBit()) {
        return 1;
    }
    else if((board[xdim*yloc+xloc]&hiddenBit())!=hiddenBit()) {
        return 2;
    }
    else if((board[xdim*yloc+xloc]&valueMask())==9) {
        board[xdim*yloc+xloc] ^=hiddenBit();
        return 9;
    }
    else if((board[xdim*yloc+xloc] & valueMask()) == 0) {
        board[xdim*yloc+xloc] ^=hiddenBit();
        //up
        if(xdim*yloc+xloc-xdim>=0) {
            if((board[xdim*yloc+xloc-xdim] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc-xdim] ^=hiddenBit();
            }
        }
        //down
        if(xdim*yloc+xloc<=(xdim*ydim-xdim)) {
            if((board[xdim*yloc+xloc+xdim] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc+xdim] ^=hiddenBit();
            }
        }
        //right
        if((xdim*yloc+xloc+1)%xdim!=0) {
            if((board[xdim*yloc+xloc+1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc+1] ^=hiddenBit();
            }
        }
        //left
        if((xdim*yloc+xloc)%xdim!=0) {
            if((board[xdim*yloc+xloc-1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc-1] ^=hiddenBit();
            }
        }
        //upleft
        if(((xdim*yloc+xloc)>=xdim) && ((xdim*yloc+xloc)%xdim!=0)) {
            if((board[xdim*yloc+xloc-xdim-1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc-xdim-1] ^=hiddenBit();
            }
        }
        //upright
        if(((xdim*yloc+xloc)>=xdim) && ((xdim*yloc+xloc+1)%xdim!=0)) {
            if((board[xdim*yloc+xloc-xdim+1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc-xdim+1] ^=hiddenBit();
            }
        }
        //downleft
        if(((xdim*yloc+xloc)<(xdim*ydim)) && ((xdim*yloc+xloc)%xdim!=0)) {
            if((board[xdim*yloc+xloc+xdim-1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc+xdim-1] ^=hiddenBit();
            }
        }
        //downright
        if(((xdim*yloc+xloc)<(xdim*ydim)) && ((xdim*yloc+xloc+1)%xdim!=0)) {
            if((board[xdim*yloc+xloc+xdim+1] & hiddenBit())==hiddenBit()){
                board[xdim*yloc+xloc+xdim+1] ^=hiddenBit();
            }
        }

    }
    else {
        board[xdim*yloc+xloc] ^=hiddenBit();
    }
    return 0;

}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    for(int i=0;i<(xdim*ydim);i++) {
        if((board[i] & valueMask()) != 9 ) {
            if(((board[i]) & hiddenBit()) == hiddenBit()) {
                return false;
            }
        }
    }
    return true;
}
