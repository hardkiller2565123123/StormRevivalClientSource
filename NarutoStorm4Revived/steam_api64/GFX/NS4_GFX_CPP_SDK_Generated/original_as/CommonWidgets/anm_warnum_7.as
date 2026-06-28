package net_event_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class anm_warnum_7 extends MovieClip
   {
      
      public var txt_warnum:smb_font;
      
      public function anm_warnum_7()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_warnum.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_warnum.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

