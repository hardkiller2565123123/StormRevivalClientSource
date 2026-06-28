package duel_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol276")]
   public dynamic class smb_cmd_10 extends MovieClip
   {
      
      public var mc_base_2:MovieClip;
      
      public var txt_cmd:smb_font;
      
      public var mc_base_1:MovieClip;
      
      public var txt_notes:smb_font;
      
      public var txt_title:smb_font;
      
      public function smb_cmd_10()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2);
      }
      
      internal function frame1() : *
      {
         stop();
         if(this.txt_title.IsArabic() == true)
         {
            this.mc_base_1.scaleX *= -1;
         }
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_LT);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_cmd.SetTextPivot(smb_font.CCD_PIVOT_LT);
         this.txt_cmd.SetTextFieldWidth(1200);
         this.txt_cmd.SetTextWordWrap(true);
         this.txt_cmd.SetTextSize(33);
         this.txt_cmd.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_notes.SetTextPivot(smb_font.CCD_PIVOT_LT);
         this.txt_notes.SetTextFieldWidth(1000);
         this.txt_notes.SetTextWordWrap(true);
         this.txt_notes.SetTextSize(30);
         this.txt_notes.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         if(this.txt_title.IsArabic() == true)
         {
            this.mc_base_2.scaleX *= -1;
         }
      }
   }
}

