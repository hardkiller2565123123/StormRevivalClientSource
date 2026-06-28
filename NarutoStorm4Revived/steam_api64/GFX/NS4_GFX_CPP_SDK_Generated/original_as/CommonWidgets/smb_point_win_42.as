package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol49")]
   public dynamic class smb_point_win_42 extends MovieClip
   {
      
      public var txt_point_w:smb_font;
      
      public var txt_num_w:smb_font;
      
      public function smb_point_win_42()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_point_w.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_point_w.SetTextColor(3280896);
         this.txt_num_w.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_num_w.SetTextColor(3280896);
      }
   }
}

