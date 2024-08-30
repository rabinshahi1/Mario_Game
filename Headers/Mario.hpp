#pragma once

class Mario
{
	bool crouching;
	bool dead;
	bool flipped;
	bool on_ground;
	bool marioDead;
	int score;
	

	
	float enemy_bounce_speed;
	float horizontal_speed;
	float vertical_speed;
	float x;
	float y;

	//The longer we press the jump button, the higher Mario jumps. And we use this variable for that.
	unsigned char jump_timer;
	
	unsigned char powerup_state;

	unsigned short death_timer;
	unsigned short growth_timer;
	unsigned short invincible_timer;

	std::vector<Mushroom> mushrooms;

	sf::Sprite sprite;

	sf::Texture texture;

	Animation big_walk_animation;
	Animation walk_animation;
public:
	Mario();
    void updateScore ();
	int getScore();
	
	void setScore();

	bool get_dead() const;

	float get_vertical_speed() const;
	float get_x() const;

	void die(const bool i_instant_death);
	void draw(sf::RenderWindow& i_window);
	void draw_mushrooms(const unsigned i_view_x, sf::RenderWindow& i_window);
	void reset();
	void set_position(const float i_x, const float i_y);
	void set_vertical_speed(const float i_value);
	void update(const unsigned i_view_x, MapManager& i_map_manager);
   bool deadMario();
	sf::FloatRect get_hit_box() const;
};