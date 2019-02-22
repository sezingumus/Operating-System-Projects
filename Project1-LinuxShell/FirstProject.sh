let "r = 0"  #we control user enter the password or not if r is equal to zero, this mean user didnt enter the password

check_password () {
  let "_count=0"  #count variable holds for user shoudnt enter 3 times password
  
	if  [ "$r" == "1" ];
	then
 	echo "You have already enter the password"
	return 1
	elif [ "$r" == "0" ];
	then
  	   echo -n "Enter the password please :" ; 
           read password
    		
           if [ "$password" == "cse333" ]; then
            echo "Access granted"
		r=1; #r hold for if user enter the password program should not ask again
            return 1
           else
            
            while  [ "$password" != "cse333" ] 
             do
             let  "_count += 1"
             if [ $_count -eq 3 ]
              then
              echo "You have reached the maximum number of trials."
              let "_count = 0"
 		exit 0 #if user enters wrong password at 3 times then program shot down
              return 0
              break
             fi     
             echo "ACCESS DENIED!"
             echo -n "Enter the password please :" ; 
             read password
             done
            fi
	fi
}

sum_exp () {

 	
	num=$1
	let "c1 = -1" #this variable holds user how many number enter
	let "total = 0" #total number (SUM)
	let "avg_count = 0" #average number
	while [ "$num" != "finish" ] #until user writes finish, program doesnt get out loop
	do		
		echo -n "Enter the number :" ; 
        	read num
		let  "c1 += 1"
		let "total += num"

	done

	if [ "$c1" == "-1" ]; then #if a number is not  entered , it will give program error
	echo "Opps something is went wrong";
	return 0
	fi

let "avg_count=total/c1"  #avg is defined in this statement
echo "Sum $total" ;       #total is defined in this statement
echo "Average $avg_count" ;

}

zero_shape () { #In this method , users enter a number that should be between 5 and 79 
                # After entering the input , this shel script will print a square that is
                # outlined with two rows/columns of asteriks
   
                #To draw outlined with two rows , an asteriks should be on the first two rows or column and last two rows or columns , 
                #other columns or rows should be blank
    for (( i=0; i< $1; i++ ))  
    do
    for (( j=0; j< $1; j++ )) 
    do
    if [ $i -lt 2 ] || [ $j -lt 2 ] || [ $i -eq $(($number-2)) ] || [ $j -eq $(($1-2)) ] || [ $i -eq $(($1-1)) ] || [ $j -eq $(($1-1)) ]; 
    then
    echo -n "*"
    else
    echo -n " "
    fi
    done
    echo " "
    done
 
}
number_2 () {
		
var=$(echo `ls -l -t | tail -1`   | awk -F" " '{print $1,$2,$3,$4,$5,$6,$7,$8,$9}')  #old file, link or directory get listed on date and time we choose last one and get information abouth that then we parse this information using space
set -- $var
# echo $1; this peace of information give us file permissions

fr=$(echo $1  | awk '{print substr($0,0,1)}') #We seperate first character and we can understand file directory or link
own=$(echo $1  | awk '{print substr($0,2,3)}') #we seperate 3 character owner group or others
gru=$(echo $1  | awk '{print substr($0,5,3)}')
othr=$(echo $1  | awk '{print substr($0,8,3)}')




 if [ "$fr" == "d" ]; then #then we can understand which one from first character 
            typ="Directory"
	elif [ "$fr" == "-" ];then
	    typ="File"
	elif [ "$fr" == "l" ];then
	    typ="Link" 
           fi


	o1=$(echo $own  | awk '{print substr($0,0,1)}') #we are seperate owner into 1 character
	o2=$(echo $own  | awk '{print substr($0,2,1)}')
	o3=$(echo $own  | awk '{print substr($0,3,1)}')
	if [ "$o1" == "r" ]; then
	o1="Read"
	fi

	if [ "$o2" == "w" ]; then
	o2="Write"
	fi

	if [ "$o3" == "x" ]; then
	o3="Execution"
	fi

	
	g1=$(echo $gru  | awk '{print substr($0,0,1)}') #we are seperate group into one character
	g2=$(echo $gru  | awk '{print substr($0,2,1)}')
	g3=$(echo $gru  | awk '{print substr($0,3,1)}')
	if [ "$g1" == "r" ]; then
	g1="Read"
	fi

	if [ "$g2" == "w" ]; then
	g2="Write"
	fi

	if [ "$g3" == "x" ]; then
	g3="Execution"
	fi
	
	echo "Others have";
	ot1=$(echo $othr  | awk '{print substr($0,0,1)}') #we are seperate Others into one character
	ot2=$(echo $othr  | awk '{print substr($0,2,1)}')
	ot3=$(echo $othr | awk '{print substr($0,3,1)}')

	if [ "$ot1" == "r" ]; then
	ot1="Read"
	fi

	if [ "$ot2" == "w" ]; then
	ot2="Write"
	fi

	if [ "$ot3" == "x" ]; then
	ot3="Execution"
	fi 
	
echo " The oldest $typ is $9 , Modified day is $7 $6 hours is $8 Owner Permission is $o1  $o2 $o3 , Group Permission is $g1 $g2 $g3 , Others Permission is $ot1 $ot2 $ot3 . Owner is $3"



}

letter_ () {

echo "What is your name?"; #This statement takes the input
read lett
sed -i -e 's|NAME|'$lett'|g' letter.txt #change NAME into lett variable
cat letter.txt #print letter.txt
}


while :
  do
     clear
     echo "-------------------------------------"
     echo " Main Menu "
     echo "-------------------------------------"
     echo "1. Password Check"
     echo "2. Find the Oldest File"           
     echo "3. Find sum and average"
     echo "4. Square of asterisks"
     echo "5. Rename the Letter"      #Until "6" is selected , this shell script executes , when 6 is choosen , 
     echo "6. Exit"                   # this program will exit.
     echo "======================="
     echo -n "Please enter your menu choice [1-6]: " 
     read yourch   #The input which will direct the choice we want to do. 
     case $yourch in  
        1)
		check_password
		echo "To continue press any key " 
		read ;;

        2)  if  [ "$r" == "1" ]; #we control if user enter the password or not
	    then
           
		number_2  #This method shows oldest file or directory or links etc and its properties 


            echo "To continue press any key " 
		elif [ "$r" == "0" ]; #if password has been not enter then give error
		then
  	   	echo -n "You have not been enter a password please return 1 and enter password" ; 
	fi
            read ;; 
 	3)	 if  [ "$r" == "1" ];
	    	then
		sum_exp
		echo "To continue press any key " 
		elif [ "$r" == "0" ];
		then
	 	echo -n "You have not been enter a password please return 1 and enter password" ; 
		fi
		read ;;
		
 	4)	 if  [ "$r" == "1" ];
	    	then
                 echo -n "Please enter a number between 5 and 79 :" ; 
                 read number
                if [ $number -lt 5 ] || [ $number -gt 79 ] ; #put a check for null variable
                 then 
      
                  while [ $number -lt 5 ] || [ $number -gt 79 ] 
                   do
                    echo -n "Out of range , please enter a valid number between 5 and 79 : "
                   read number
                     done
                     fi
		zero_shape $number
		echo "To continue press any key " 

		elif [ "$r" == "0" ];
		then
	 	echo -n "You have not been enter a password please return 1 and enter password" ; 
		fi 
		read ;;

        5)	 if  [ "$r" == "1" ];
	    	then
		letter_  #This method writes a letter with a name we enter
		echo "To continue press any key "  
		elif [ "$r" == "0" ];
		then
	 	echo -n "You have not been enter a password please return 1 and enter password" ; 
		fi 
		read ;;
 	6) clear #To close the program
           exit 0 ;;
 	*) echo "Opps!!! Please select choice 1,2,3,4,5 or 6";
 	   echo "Press a key. . ." ; read ;;
     esac
  done
