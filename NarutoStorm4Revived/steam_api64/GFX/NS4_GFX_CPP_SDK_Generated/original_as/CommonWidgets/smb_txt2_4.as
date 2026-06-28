package info_mision_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class smb_txt2_4 extends MovieClip
   {
      
      public var txt_suc:smb_font;
      
      public function smb_txt2_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_suc.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_suc.SetTextSize(27);
         this.txt_suc.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
      }
   }
}

