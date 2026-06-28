package collect_skill_fla
{
   import flash.display.MovieClip;
   import script.icon_confirm.nut_conf_l;
   import script.xcmn_menu.nut_cursor_m;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public dynamic class anm_player00_4 extends MovieClip
   {
      
      public var all_conf_l:nut_conf_l;
      
      public var all_cursor_m:nut_cursor_m;
      
      public var dmy_charaicon:nut_tex00;
      
      public function anm_player00_4()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame3() : *
      {
         stop();
      }
   }
}

