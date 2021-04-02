#! /bin/bash

make > /dev/null

ret=`./minishell "'toto'
" 2>&1`
if [[ $ret != "toto" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi


ret=`./minishell "'to to'
" 2>&1`
if [[ $ret != "to to" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi

ret=`./minishell "'to to'tata
" 2>&1`
if [[ $ret != "to totata" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi

ret=`./minishell "'toto'tata
" 2>&1`
if [[ $ret != "tototata" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi

ret=`./minishell "tata'toto'
" 2>&1`
if [[ $ret != "tatatoto" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi

ret=`./minishell "tata'toto'ta
" 2>&1`
if [[ $ret != "tatatotota" ]]
then
	echo t 1 merd
else
	echo t 1 bg
fi
