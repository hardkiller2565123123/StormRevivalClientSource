package map_sm_brt_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol48")]
   public dynamic class anm_txt_15 extends MovieClip
   {
      
      public var txt_num:smb_font;
      
      public function anm_txt_15()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_num.SetTextSize(28);
         this.txt_num.SetTextColor(16769700);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
      }
   }
}

