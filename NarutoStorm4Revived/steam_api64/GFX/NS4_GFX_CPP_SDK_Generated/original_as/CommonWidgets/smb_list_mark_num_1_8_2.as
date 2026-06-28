package freebtl_leag_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol15")]
   public dynamic class smb_list_mark_num_1_8 extends MovieClip
   {
      
      public var txt_list_score:smb_font;
      
      public function smb_list_mark_num_1_8()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_list_score.SetTextSize(57);
         this.txt_list_score.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_list_score.SetTextColor(9895936);
      }
   }
}

