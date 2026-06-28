package net_seach_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol13")]
   public dynamic class smb_room_4 extends MovieClip
   {
      
      public var txt_room:smb_font;
      
      public function smb_room_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_room.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_room.SetTextColor(9906944);
         this.txt_room.SetTextFieldWidth(800);
         this.txt_room.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_room.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_room.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_room.SetTextFieldWidth(800);
         this.txt_room.SetTextFit(true);
      }
   }
}

