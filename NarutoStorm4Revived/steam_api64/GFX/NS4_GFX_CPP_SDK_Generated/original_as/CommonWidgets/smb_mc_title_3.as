package custom_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public dynamic class smb_mc_title_3 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function smb_mc_title_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_title.SetTextSize(33);
      }
   }
}

