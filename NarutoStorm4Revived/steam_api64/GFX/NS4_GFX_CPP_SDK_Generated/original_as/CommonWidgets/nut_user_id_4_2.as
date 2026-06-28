package net_offline_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class nut_user_id_4 extends MovieClip
   {
      
      public var txt_user_id:smb_font;
      
      public function nut_user_id_4()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_user_id.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_user_id.SetTextSize(28);
      }
   }
}

