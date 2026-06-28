package net_event_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class smb_char_bg_3 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function smb_char_bg_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

