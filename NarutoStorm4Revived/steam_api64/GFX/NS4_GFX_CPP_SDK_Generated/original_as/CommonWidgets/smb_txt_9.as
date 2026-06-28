package info_mision_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class smb_txt_9 extends MovieClip
   {
      
      public var txt_suc:smb_font;
      
      public function smb_txt_9()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_suc.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_suc.SetTextSize(30);
         this.txt_suc.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

