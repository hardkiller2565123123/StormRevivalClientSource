package script.stage_logos
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol18")]
   public class all_stage_logo_index extends MovieClip
   {
      
      public var logo_link1:storm_one;
      
      public var logo_link2:storm_two;
      
      public var logo_link3:storm_gen;
      
      public var logo_link4:storm_three;
      
      public var logo_link5:storm_three_fb;
      
      public var logo_link6:storm_rev;
      
      public var logo_link7:storm_four;
      
      public var logo_link8:storm_four_rtb;
      
      public var logo_link9:storm_four_evo;
      
      public var logo_link10:storm_con;
      
      public var logo_link11:shinobi_striker;
      
      private const LOOP_FRAME:* = 15;
      
      private var m_anmList:Array = new Array();
      
      private var m_phase:int;
      
      private var m_loopFrame:int;
      
      private var m_queuedPhase:int = -1;
      
      public function all_stage_logo_index()
      {
         super();
         this.m_anmList.push(this["logo_link1"]);
         this.m_anmList.push(this["logo_link2"]);
         this.m_anmList.push(this["logo_link3"]);
         this.m_anmList.push(this["logo_link4"]);
         this.m_anmList.push(this["logo_link5"]);
         this.m_anmList.push(this["logo_link6"]);
         this.m_anmList.push(this["logo_link7"]);
         this.m_anmList.push(this["logo_link8"]);
         this.m_anmList.push(this["logo_link9"]);
         this.m_anmList.push(this["logo_link10"]);
         this.m_anmList.push(this["logo_link11"]);
         var _loc1_:int = 0;
         while(_loc1_ < this.m_anmList.length)
         {
            this.m_anmList[_loc1_].stop();
            this.m_anmList[_loc1_].visible = false;
            _loc1_++;
         }
         this.m_phase = 0;
         this.m_loopFrame = 0;
      }
      
      public function PlayAnm(idx:int) : void
      {
         if(idx < 0 || idx >= m_anmList.length)
         {
            return;
         }
         for each(var c in m_anmList)
         {
            c.visible = false;
            c.stop();
            c.removeEventListener(Event.ENTER_FRAME,onEnterFrame);
         }
         var show:MovieClip = m_anmList[idx];
         m_phase = idx;
         show.visible = true;
         show.gotoAndPlay("in");
         show.addEventListener(Event.ENTER_FRAME,onEnterFrame);
      }
      
      private function onEnterFrame(e:Event) : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(clip.currentLabel == "loop")
         {
            clip.removeEventListener(Event.ENTER_FRAME,onEnterFrame);
            clip.stop();
         }
      }
      
      public function Out() : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(!clip)
         {
            return;
         }
         clip.addEventListener(Event.ENTER_FRAME,onOutFrame);
         clip.gotoAndPlay("out");
      }
      
      public function OutAndQueue(nextPhase:int) : void
      {
         m_queuedPhase = nextPhase;
         var clip:MovieClip = m_anmList[m_phase];
         clip.addEventListener(Event.ENTER_FRAME,onOutEnterFrame);
         clip.gotoAndPlay("out");
      }
      
      private function onOutEnterFrame(e:Event) : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(clip.currentLabel == "end")
         {
            clip.removeEventListener(Event.ENTER_FRAME,onOutEnterFrame);
            if(m_queuedPhase >= 0)
            {
               PlayAnm(m_queuedPhase);
               m_queuedPhase = -1;
            }
         }
      }
      
      private function onOutFrame(e:Event) : void
      {
         var clip:MovieClip = m_anmList[m_phase];
         if(clip.currentLabel == "end" || clip.currentLabel == "outEnd")
         {
            clip.removeEventListener(Event.ENTER_FRAME,onOutFrame);
            clip.visible = false;
         }
      }
   }
}

