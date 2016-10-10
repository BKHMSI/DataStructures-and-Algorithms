//
//  AI.h
//  TicTacToe Cmd
//
//  Created by Badr AlKhamissi on 1/21/16.
//  Copyright © 2016 Badr AlKhamissi. All rights reserved.
//


/** Minimax with Alpha Beta Pruning **/

#ifndef AI_h
#define AI_h

#include <iostream>
#include <vector>
#include <set>
#include "Board.h"

using namespace std;


class AI{
private:
    struct AIMove{
        int x, y, score;
        AIMove(){}
        AIMove(int _s):score(_s){}
        AIMove(int _x, int _y){x = _x, y = _y; score = 0;}
        AIMove(int _x, int _y, int _s){x = _x, y = _y; score = _s;}
        void operator = (const AIMove& rhs){ x = rhs.x; y = rhs.y; score = rhs.score;}
        bool operator > (const AIMove& rhs)const{ return score>rhs.score;}
        bool operator >= (const AIMove& rhs)const{ return score>=rhs.score;}
        bool operator < (const AIMove& rhs)const{ return score<rhs.score;}
        bool operator <= (const AIMove& rhs)const{ return score<=rhs.score;}
        bool operator == (const AIMove& rhs)const{ return score==rhs.score;}
        AIMove operator - (){return AIMove(this->x, this->y,-this->score); }
    };
public:
    void makeMove(Board&, player);
    AIMove getBestMove(Board&,player);
    AIMove alphaBeta(Board&,AIMove,AIMove,int,player);
    AIMove alphaBetaNegamax(Board&,AIMove,AIMove,player);
};

void AI::makeMove(Board& board, player p){
    AIMove bestMove = alphaBeta(board,AIMove(INT_MIN),AIMove(INT_MAX),16,p);
    cout<<"AI Score: "<<bestMove.score*-1<<endl;
    board.setVal(bestMove.x, bestMove.y, p);
}

AI::AIMove AI::getBestMove(Board& board, player playerTurn){
    
    state gameState = board.checkWin(playerTurn);
    if(gameState == win){
        return AIMove(10);
    }else if(gameState == lose){
        return AIMove(-10);
    }else if(gameState == draw){
        return AIMove(0);
    }
    
    vector<AIMove>moves;
    
    for (int i = 0; i<board.getSize(); i++) {
        for (int j = 0; j<board.getSize(); j++) {
            if(board.isEmpty(i,j)){
                AIMove move(i,j);
                board.setVal(i, j, playerTurn);
                
                if(playerTurn == player_2)
                    move.score = getBestMove(board, player_1).score;
                else
                    move.score = getBestMove(board, player_2).score;
                
                moves.push_back(move);
                board.setVal(i,j,empty);
            }
        }
    }
    
    int bestMove = 0;
    if(playerTurn == player_2){
        int min = INT_MAX;
        for (int i = 0; i<moves.size(); i++) {
            if(moves[i].score < min) min = moves[i].score, bestMove = i;
        }
    }else{
        int max = INT_MIN;
        for (int i = 0; i<moves.size(); i++) {
            if(moves[i].score > max) max = moves[i].score, bestMove = i;
        }
    }
    
    return moves[bestMove];
}

AI::AIMove AI::alphaBeta(Board& board, AIMove alpha, AIMove beta, int depth, player player){
    
    state gameState = board.checkWin(player);
    if(gameState == win){
        return AIMove(10);
    }else if(gameState == lose){
        return AIMove(-10);
    }else if(gameState == draw || !depth){
        return AIMove(0);
    }
    
    if(player == player_1){
        for (int i = 0; i<board.getSize(); i++) {
            for (int j = 0; j<board.getSize(); j++) {
                if(board.isEmpty(i,j)){
                    AIMove move(i,j);
                    board.setVal(i, j, player);
                    move.score = alphaBeta(board, alpha, beta, depth-1, player_2).score;
                    board.setVal(i,j,empty);
                    if (move > alpha)
                        alpha = move;
                    if(alpha>=beta)
                        return alpha;
                }
            }
        }
        return alpha;
    }else{
        for (int i = 0; i<board.getSize(); i++) {
            for (int j = 0; j<board.getSize(); j++) {
                if(board.isEmpty(i,j)){
                    AIMove move(i,j);
                    board.setVal(i, j, player);
                    move.score = alphaBeta(board, alpha, beta, depth-1, player_1).score;
                    board.setVal(i,j,empty);
                    if (move < beta)
                        beta = move;
                    if(alpha>=beta)
                        return beta;
                }
            }
        }
        return beta;
    }
}

AI::AIMove AI::alphaBetaNegamax(Board& board, AIMove alpha, AIMove beta, player player){
    
    state gameState = board.checkWin(player);
    if(gameState == win){
        return AIMove(10);
    }else if(gameState == lose){
        return AIMove(-10);
    }else if(gameState == draw){
        return AIMove(0);
    }
    
    for (int i = 0; i<board.getSize(); i++) {
        for (int j = 0; j<board.getSize(); j++) {
            if(board.isEmpty(i,j)){
                alpha.x = i, alpha.y = j;
                board.setVal(i, j, player);
                if(player == player_1)
                    alpha = max(alpha,-alphaBetaNegamax(board, -beta, -alpha, player_2));
                else
                    alpha = max(alpha,-alphaBetaNegamax(board, -beta, -alpha, player_1));
                
                board.setVal(i,j,empty);
                
                if(beta.score >= alpha.score)
                    return alpha;
            }
        }
    }
    return alpha;
}


#endif /* AI_h */
