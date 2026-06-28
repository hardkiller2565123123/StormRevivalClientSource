package start_ning_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol21")]
   public dynamic class smb_txt_own_12 extends MovieClip
   {
      
      public var txt_own:smb_font;
      
      public function smb_txt_own_12()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_own.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_own.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_own.SetTextSize(30);
      }
   }
}

