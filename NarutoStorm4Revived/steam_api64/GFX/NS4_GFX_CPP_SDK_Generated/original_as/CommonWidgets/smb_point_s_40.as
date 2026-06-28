package freebtl_cp_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol41")]
   public dynamic class smb_point_s_40 extends MovieClip
   {
      
      public var txt_point:smb_font;
      
      public var txt_num:smb_font;
      
      public function smb_point_s_40()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_point.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_point.SetTextColor(3280896);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_RC);
         this.txt_num.SetTextColor(3280896);
      }
   }
}

