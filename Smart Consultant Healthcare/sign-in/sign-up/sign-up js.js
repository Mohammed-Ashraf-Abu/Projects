function EMail_validate()  
    {  
        var x=document.myForm.EMail.value;  
        var atposition=x.indexOf("@");  
        var dotposition=x.lastIndexOf(".");  
        if (atposition<1 || dotposition<atposition+2 || dotposition+2>=x.length)
        {  
            alert("Please enter a valid e-mail address \n atpostion:"+atposition+"\n dotposition:"+dotposition);  
            return false;  
        }  
     }
 function validate()
     {
         if( document.myForm.Password.value == "" )
        {
            alert( "Please provide your Password!" );
            document.myForm.Password.focus() ;
            return false;
        }
        
   if( document.myForm.phone.value == "" ||
   isNaN( document.myForm.phone.value ) ||
   document.myForm.phone.value.length != 10 )
   {
   alert( "Please provide the phonenumber in the format ##########." );
   document.myForm.phone.focus() ;
   return false;
   }
        return(true);
     }