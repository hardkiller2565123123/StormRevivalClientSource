package hist_cmn_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public dynamic class anm_bns_title_29 extends MovieClip
   {
      
      public var txt_title:smb_font;
      
      public function anm_bns_title_29()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_title.SetTextSize(30);
         this.txt_title.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_title.SetTextColor(16777215);
      }
   }
}

