package load_cmn_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class smb_txt_load_6 extends MovieClip
   {
      
      public var txt_load00:smb_font;
      
      public function smb_txt_load_6()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_load00.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_load00.SetTextSize(28);
      }
   }
}

