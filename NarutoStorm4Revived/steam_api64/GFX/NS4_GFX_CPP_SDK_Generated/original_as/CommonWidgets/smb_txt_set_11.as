package freebtl_leag_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol33")]
   public dynamic class smb_txt_set_11 extends MovieClip
   {
      
      public var txt_set:smb_font;
      
      public function smb_txt_set_11()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_set.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_set.SetTextSize(47);
         this.txt_set.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_set.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

