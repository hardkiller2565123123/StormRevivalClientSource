package load_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class smb_txt_per_5 extends MovieClip
   {
      
      public var txt_per00:smb_font;
      
      public function smb_txt_per_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_per00.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_per00.SetTextSize(28);
      }
   }
}

