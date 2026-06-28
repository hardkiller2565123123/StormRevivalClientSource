package hist_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol49")]
   public dynamic class anm_title_5 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function anm_title_5()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextSize(39);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(16771175);
         this.txt_title.SetTextFieldWidth(780);
         this.txt_title.SetTextFit(true);
      }
   }
}

