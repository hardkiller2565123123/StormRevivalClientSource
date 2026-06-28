package script.duel_boss_sf
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol12")]
   public class nut_sf_get extends MovieClip
   {
      
      public var mc_sf1:MovieClip;
      
      public var mc_sf2:MovieClip;
      
      public var mc_sf3:MovieClip;
      
      public var mc_sf4:MovieClip;
      
      private const CCD_WAIT_FRAMES:int = 5;
      
      private var m_stars:Array = new Array();
      
      private var m_waitCount:int = 0;
      
      public function nut_sf_get()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_stars[0] = MovieClip(this.getChildByName("mc_sf1"));
         this.m_stars[1] = MovieClip(this.getChildByName("mc_sf2"));
         this.m_stars[2] = MovieClip(this.getChildByName("mc_sf3"));
         this.m_stars[3] = MovieClip(this.getChildByName("mc_sf4"));
         var _loc1_:int = 0;
         while(_loc1_ < this.m_stars.length)
         {
            this.m_stars[_loc1_].visible = false;
            this.m_stars[_loc1_].gotoAndStop("in");
            _loc1_++;
         }
      }
      
      public function PlayGetStarsCutin(param1:Number, param2:Number, param3:int) : *
      {
         removeEventListener(Event.ENTER_FRAME,this.UpdateLoopOutAnm);
         removeEventListener(Event.ENTER_FRAME,this.UpdateInAnm);
         var _loc4_:int = 0;
         while(_loc4_ < this.m_stars.length)
         {
            this.m_stars[_loc4_].visible = false;
            this.m_stars[_loc4_].gotoAndStop("in");
            _loc4_++;
         }
         this.visible = true;
         this.x = param1;
         this.y = param2;
         if(param3 == 1)
         {
            this.gotoAndStop("sf1");
         }
         else if(param3 == 2)
         {
            this.gotoAndStop("sf2");
         }
         else if(param3 == 3)
         {
            this.gotoAndStop("sf3");
         }
         else if(param3 == 4)
         {
            this.gotoAndStop("sf4");
         }
         else
         {
            this.visible = false;
         }
         this.m_stars[0].visible = true;
         this.m_stars[0].gotoAndPlay("in");
         this.m_waitCount = 0;
         addEventListener(Event.ENTER_FRAME,this.UpdateInAnm);
      }
      
      public function UpdateInAnm(param1:Event) : *
      {
         var _loc2_:int = 1;
         while(_loc2_ < this.m_stars.length)
         {
            if(Boolean(this.m_stars[_loc2_ - 1]) && this.m_stars[_loc2_ - 1].currentLabel == "in_next")
            {
               if(Boolean(this.m_stars[_loc2_]) && this.m_stars[_loc2_].visible == false)
               {
                  this.m_stars[_loc2_].visible = true;
                  this.m_stars[_loc2_].gotoAndPlay("in");
               }
            }
            _loc2_++;
         }
         if(Boolean(this.m_stars[this.m_stars.length - 1]) && this.m_stars[this.m_stars.length - 1].currentLabel == "loop")
         {
            if(++this.m_waitCount > this.CCD_WAIT_FRAMES)
            {
               this.m_stars[0].gotoAndPlay("out");
               removeEventListener(Event.ENTER_FRAME,this.UpdateInAnm);
               addEventListener(Event.ENTER_FRAME,this.UpdateLoopOutAnm);
            }
         }
      }
      
      public function UpdateLoopOutAnm(param1:Event) : *
      {
         var _loc2_:int = 0;
         _loc2_ = 1;
         while(_loc2_ < this.m_stars.length)
         {
            if(Boolean(this.m_stars[_loc2_ - 1]) && this.m_stars[_loc2_ - 1].currentLabel == "out_next")
            {
               if(Boolean(this.m_stars[_loc2_]) && this.m_stars[_loc2_].currentLabel == "loop")
               {
                  this.m_stars[_loc2_].visible = true;
                  this.m_stars[_loc2_].gotoAndPlay("out");
               }
            }
            _loc2_++;
         }
         if(Boolean(this.m_stars[this.m_stars.length - 1]) && this.m_stars[this.m_stars.length - 1].currentLabel == "end")
         {
            _loc2_ = 0;
            while(_loc2_ < this.m_stars.length)
            {
               this.m_stars[_loc2_].visible = false;
               this.m_stars[_loc2_].gotoAndStop("in");
               _loc2_++;
            }
            removeEventListener(Event.ENTER_FRAME,this.UpdateLoopOutAnm);
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

