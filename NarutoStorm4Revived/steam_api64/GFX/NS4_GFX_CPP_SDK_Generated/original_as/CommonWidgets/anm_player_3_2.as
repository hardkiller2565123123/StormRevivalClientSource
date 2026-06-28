package collect_skill_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xct_base1.nut_base1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_player_3 extends MovieClip
   {
      
      public var txt_leader:smb_font;
      
      public var mc_tex_2:nut_base1;
      
      public var all_player02:MovieClip;
      
      public var all_player01:MovieClip;
      
      public var mc_tex_1:nut_base1;
      
      public var all_player00:MovieClip;
      
      public function anm_player_3()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_leader.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_leader.SetTextColor(16776833);
         this.txt_leader.SetTextSize(30);
         this.txt_leader.SetTextFieldWidth(436);
         this.txt_leader.SetTextFit(true);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_leader.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_leader.SetTextColor(16776833);
         this.txt_leader.SetTextSize(30);
         this.txt_leader.SetTextFieldWidth(436);
         this.txt_leader.SetTextFit(true);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_leader.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_leader.SetTextColor(16776833);
         this.txt_leader.SetTextSize(30);
         this.txt_leader.SetTextFieldWidth(436);
         this.txt_leader.SetTextFit(true);
      }
   }
}

