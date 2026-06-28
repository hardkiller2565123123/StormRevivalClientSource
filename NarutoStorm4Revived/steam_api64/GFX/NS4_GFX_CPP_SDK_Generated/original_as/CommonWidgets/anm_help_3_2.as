package preset_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_unset.smb_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_help_3 extends MovieClip
   {
      
      public var txt_help:smb_font;
      
      public var mc_base:smb_base;
      
      public function anm_help_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_help.SetTextSize(30);
         this.txt_help.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_help.SetTextFieldWidth(650);
         this.txt_help.SetTextFit(true);
      }
   }
}

