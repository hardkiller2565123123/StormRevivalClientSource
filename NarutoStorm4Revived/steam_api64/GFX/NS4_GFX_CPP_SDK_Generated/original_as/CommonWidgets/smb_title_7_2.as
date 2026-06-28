package option_keyboard_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public dynamic class smb_title_7 extends MovieClip
   {
      
      public var txt_main_title:smb_font;
      
      public function smb_title_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_main_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_main_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

