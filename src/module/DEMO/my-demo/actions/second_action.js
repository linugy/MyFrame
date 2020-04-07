 (
   { 
     label: "SecondButton",
     run: function() { 
       var text = this.getCurText(); 
       var label = new MyLabel;
       label.setText(text);
       label.show();
     }
   }
 )