package net_offline_fla
{
   import flash.display.MovieClip;
   import script.net_result.nut_rsult_p;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class nut_match_3 extends MovieClip
   {
      
      public var mc_menubar00:MovieClip;
      
      public var mc_menubar01:MovieClip;
      
      public var txt_info:smb_font;
      
      public var txt_head:smb_font;
      
      public var all_user_id:MovieClip;
      
      public var all_rsult_p:nut_rsult_p;
      
      public function nut_match_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.txt_head.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_head.SetTextColor(15058221);
         this.txt_info.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_info.SetTextFieldWidth(1150);
         this.txt_info.SetTextWordWrap(true);
      }
   }
}

