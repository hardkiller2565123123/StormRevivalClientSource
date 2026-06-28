package duel_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol283")]
   public dynamic class smb_head_13 extends MovieClip
   {
      
      public var txt_head:smb_font;
      
      public function smb_head_13()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_head.SetTextSize(30);
      }
   }
}

