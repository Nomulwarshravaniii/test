create()
{
  echo "Enter address book name "
  read ab
  #check address book is available or not in current working dir
  res=`ls | grep $ab | wc -w`
  if [ $res -gt 0 ]
  then 
      echo "Error: file already exits "
  else 
      touch $ab
      echo "Address Book created"
  fi
}
display()
{
  echo "Enter address book name "
  read ab
  
  res=`ls |grep $ab | wc -w`
  
  if [ $res -gt 0 ]
  then 
      cat $ab
  else
      echo "Error:File does not exist "
  fi
  
}
insert() {
  echo "Enter address book name "
  read ab
  
  res=`ls | grep $ab | wc -w`
  
  if [ $res -gt 0 ]; then 
      
      while true; do
          echo "Enter email "
          read email
          # Validate email format using regex
          if [[ "$email" =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
              break
          else
              echo "Invalid email format. Please try again."
          fi
      done
      # Check if email is already in the address book
      len=`cat $ab | grep $email | wc -w` 
      if [ $len -gt 0 ]; then 
          echo "Error: Email already exists"
      else
          while true; do
              echo "Enter First name"
              read fname
              if [[ "$fname" =~ ^[a-zA-Z]+$ ]]; then
                  break
              else
                  echo "Invalid First name. Please enter alphabetic characters only."
              fi
          done

          while true; do
              echo "Enter Last name"
              read lname
              if [[ "$lname" =~ ^[a-zA-Z]+$ ]]; then
                  break
              else
                  echo "Invalid Last name. Please enter alphabetic characters only."
              fi
          done

          while true; do
              echo "Enter Mobile number"
              read mobile
              if [[ "$mobile" =~ ^[0-9]{10}$ ]]; then
                  break
              else
                  echo "Invalid Mobile number. Please enter a 10-digit number."
              fi
          done

          record=`echo $fname $lname $email $mobile`
          echo $record >> $ab
          echo "Record Inserted"
      fi
  else
      echo "Error: Address book does not exist"
  fi
}
search()
{
	echo "Enter address book name "
	read ab
	
	#check if address book is present or not
	res=`ls | grep $ab | wc -w`
	if [ $res -gt 0 ]
	then 
		echo "Address book  present "
		echo "Enter email "
		read email
		
		len=`cat $ab | grep $email | wc -w`
		if [ $len -gt 0 ]
		then 
			echo "Email found "
			return
		else
			echo "Email not found "
			return
		fi
	
	else
		echo "Address book not found"
	fi
		
	
}
modify() {
    echo "Enter address book name "
    read ab
    
    res=`ls | grep $ab | wc -w`
    if [ $res -gt 0 ]; then 
        echo "Enter email"
        read email
        
        len=`cat $ab | grep $email | wc -w`
        
        if [ $len -gt 0 ]; then 
            while true; do
                echo "Enter modified First name"
                read fname
                if [[ "$fname" =~ ^[a-zA-Z]+$ ]]; then
                    break
                else
                    echo "Invalid First name. Please enter alphabetic characters only."
                fi
            done

            while true; do
                echo "Enter modified Last name"
                read lname
                if [[ "$lname" =~ ^[a-zA-Z]+$ ]]; then
                    break
                else
                    echo "Invalid Last name. Please enter alphabetic characters only."
                fi
            done

            while true; do
                echo "Enter modified Mobile number"
                read mobile
                if [[ "$mobile" =~ ^[0-9]{10}$ ]]; then
                    break
                else
                    echo "Invalid Mobile number. Please enter a 10-digit number."
                fi
            done

            new=`echo $fname $lname $email $mobile`
            old=`cat $ab | grep $email`
            
            echo "Old record: $old"
            echo "New record: $new"
            
            sed -i  s/"$old"/"$new"/g $ab
            echo "Record Modified"
        else
            echo "Error: Email does not exist"
        fi
    else
        echo "Error: Address book does not exist"
    fi
}
delete()
{
echo "Enter address book name "
	read ab
	
	#check if address book is present or not
	res=`ls | grep $ab | wc -c`
	if [ $res -gt 0 ]
	then 
		echo "Enter email"
		read email
		
		len=`cat $ab | grep $email | wc -w`
		
		if [ $len -gt 0 ]
		then 
			old=`cat $ab | grep $email`
			
			
			sed -i s/"$old"// $ab
			sed -i /^s/d $ab
			echo "Record deleted"
		else
			echo "Emial does not exits"
		fi
	else
		echo "File does not exits"
	fi
	
}
while [ true ]  
do
    echo "****Menu*******"
    echo "1.Create"
    echo "2.Display"
    echo "3.Insert record"
    echo "4.Search"
    echo "5.Modify"
    echo "6.Delete"
    echo "7.exit"
    
    echo "Enter Choice "
    read choice
    
    case $choice in
        1)create;;
        2)display;;
        3)insert;;
        4)search;;
        5)modify;;
        6)delete;;
        7)exit;;
        *)echo "Wrong choice ";;
    esac
done