package net_banner_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class smb_font_cover_4 extends MovieClip
   {
      
      public var txt_event:smb_font;
      
      public var txt_period:smb_font;
      
      public function smb_font_cover_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_event.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_event.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_event.SetTextSize(28);
         this.txt_event.SetTextFieldWidth(480);
         this.txt_event.SetTextScroll(true);
         this.txt_period.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_period.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_period.SetTextSize(25);
      }
   }
}

